import finufft
import mrcfile
import numpy as np
import matplotlib.pyplot as plt
from scipy import ndimage as ndi


def log_abs(array):
    return np.log(1 + np.abs(array))


def ft2(array):
    return np.fft.fftshift(np.fft.fft2(array))


def ift2(array):
    return np.fft.ifft2(np.fft.ifftshift(array)).real


def ftn(array):
    return np.fft.fftshift(np.fft.fftn(array))


def iftn(array):
    return np.fft.ifftn(np.fft.ifftshift(array)).real


def get_random_euler_angles(n=1):
    return np.random.uniform(0, 2*np.pi, (n, 3))


def rot_matrix_2d(theta):
    return np.array([[np.cos(theta), -np.sin(theta)],
                     [np.sin(theta),  np.cos(theta)]])


def open_mrc(mrc_file, return_voxel=False):
    with mrcfile.open(mrc_file) as mrc:
        x = mrc.data
        voxel = mrc.voxel_size.x
        mrc.close()
        if return_voxel:
            x = [x, voxel]
    
    return x


def radial_distance_grid(shape):
    """Compute grid of radial distances"""
    
    center = [n//2 for n in shape]
    idx = [slice(-center[i], l-center[i]) for i, l in enumerate(shape)] 
    coords = np.ogrid[idx] # zero-centered grid index
    square_coords = [c**2 for c in coords] # square grid for distance (x^2 + y^2 + z^2 = r^2)
    
    radial_dists = square_coords[0] # initialize to broadcast distance grid by dimension
    for dimension in range(1, len(shape)):
        radial_dists = radial_dists + square_coords[dimension]
        
    return np.round(np.sqrt(radial_dists))


def sphere_mask(r_dists, radius=False):
    """Returns sphere mask as boolean"""
    
    if not radius:
        center = [n//2 for n in r_dists.shape]
        radius = np.amin(center)
        
    mask = r_dists <= radius
    
    return mask


def fourier_downsample(array, factor=1, rescale=False):
    """Downsample array by cropping its Fourier transform (factor 2 would give 100pix -> 50pix)"""
    
    assert factor >= 1, "scale factor must be greater than 1"
    
    shape = array.shape
    center = [d//2 for d in shape]
    new_shape = [int(d / factor) for d in shape]
    
    F = ftn(array)
    idx = tuple([slice(center[i] - new_shape[i]//2, center[i] + new_shape[i]//2) for i in range(len(shape))])
    F = F[idx] 
    
    if rescale:
        F = F * (np.product(new_shape) / np.product(shape))
    
    f_downsample = iftn(F)
    
    return f_downsample

### =====================================================
### functions to compute fast common lines between pairs 
### =====================================================
### - do we want to use L2 or EMD, real space or Fourier sapce?
### - do we want to include shifting or not (i.e. use circular conv for each pair)?
### - do we need a ramp for L2 dist in Fourier space?
### - switch to high level BLAS instead of loop with np linalg norm?

### - comparing two LxL images with L lines is L^3 operations
### - comparing two LxL images with L lines and all shifts is L^4 operations or L^3 log(L) with circ conv

### - can speed this up by not recomputing NUFFT each iteration e.g. (img0, img1), (img0, img2)...

def line_projection_distances(img_1, img_2, angles, apply_ramp=False, dist_domain='Real'):
    """compute line projection distances using Euclidean distance"""
    
    nufft_type=2; n_trans=1; eps=1e-8 
    
    ny, nx = img_1.shape

    rads = angles / 180 * np.pi
    n_lines = len(rads)

    y_idx = np.arange(-ny / 2, ny / 2) / ny * 2

    x_theta = y_idx[:, np.newaxis] * np.sin(rads)[np.newaxis, :]
    x_theta = np.pi * x_theta.flatten()

    y_theta = y_idx[:, np.newaxis] * np.cos(rads)[np.newaxis, :]
    y_theta = np.pi * y_theta.flatten()

    plan = finufft.Plan(nufft_type, (nx, ny), n_trans, eps)
    plan.setpts(x_theta, y_theta)

    img_1_f = plan.execute(img_1.astype(np.complex128))
    img_1_f = img_1_f.reshape(ny, n_lines) 

    img_2_f = plan.execute(img_2.astype(np.complex128))
    img_2_f = img_2_f.reshape(ny, n_lines)

    if apply_ramp:
        freqs = np.abs(np.pi * y_idx)

        img_1_f *= freqs[:, np.newaxis]
        img_2_f *= freqs[:, np.newaxis]      
        
    if dist_domain == 'Real':   
        img_1_f = np.fft.fftshift(np.fft.ifft(np.fft.ifftshift(img_1_f, axes=0), axis=0), axes=0).real
        img_2_f = np.fft.fftshift(np.fft.ifft(np.fft.ifftshift(img_2_f, axes=0), axis=0), axes=0).real 

    ### scores img1 -> img2 == img2 --> img1 (if comparing many images later)
    ### add option to store all scores at all angles
    ### add option to compute distance in real vs Fourier space (when to filter)
    
    scores = []
    
    for j in range(n_lines):

        l2j = img_2_f[:, j]

        dists = np.linalg.norm(img_1_f - l2j[:, np.newaxis], axis=0)
        d_min_idx = np.argmin(dists)

        a1 = angles[d_min_idx]  # angle for cl in image_1
        a2 = angles[j]  # angle for cl in image_2

        d_min = dists[d_min_idx]

        scores.append((d_min, a1, a2))

    cl = min(scores, key = lambda x: x[0])
            
    return cl


def compute_common_line_angles(images, angles):
    
    n_total = images.shape[0]
    
    cl_angles = {(i, j): [] for i in range(n_total) for j in range(i+1, n_total)}
    
    for i in range(n_total):
        for j in range(i+1, n_total):
            d, aij, aji = line_projection_distances(images[i], images[j], angles)        
            cl_angles[(i, j)] = [aij, aji]
            
    return cl_angles


def form_cl_matrix_from_cl_angles(cl_angles, n_total):
    
    A = np.zeros((2*n_total, n_total))

    point = np.array([[1, 0]]).T

    for pair, angles in cl_angles.items():
        i, j = pair

        theta_ij = np.deg2rad(angles[0])
        theta_ji = np.deg2rad(angles[1])

        Ri = rot_matrix_2d(theta_ij)
        Rj = rot_matrix_2d(theta_ji)

        ri = Ri @ point
        rj = Rj @ point

        A[2*i:2*i+2, j] = ri.T  
        A[2*j:2*j+2, i] = rj.T
        
    return A


# =======================
#     plotting utils
# =======================


def two_plot(image_1, image_2, size=5, color='viridis'):
    fig, axs = plt.subplots(1, 2, figsize=(size, size))
    axs[0].imshow(image_1, cmap=color)
    axs[0].axis('off')
    axs[1].imshow(image_2, cmap=color)
    axs[1].axis('off')
    fig.tight_layout()
    plt.show()