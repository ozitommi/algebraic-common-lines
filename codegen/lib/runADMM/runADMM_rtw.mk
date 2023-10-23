###########################################################################
## Makefile generated for component 'runADMM'. 
## 
## Makefile     : runADMM_rtw.mk
## Generated on : Sun Oct 22 15:26:36 2023
## Final product: ./runADMM.a
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# MODELLIB                Static library target

PRODUCT_NAME              = runADMM
MAKEFILE                  = runADMM_rtw.mk
MATLAB_ROOT               = /Applications/MATLAB_R2023a.app
MATLAB_BIN                = /Applications/MATLAB_R2023a.app/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/maci64
START_DIR                 = /Users/ozitommi/Documents/MATLAB/Higher\ Order\ Sychronization/algebraic_constraints_22-10-2023
TGT_FCN_LIB               = ISO_C
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = ../../..
C_STANDARD_OPTS           = -fno-common -fexceptions
CPP_STANDARD_OPTS         = -std=c++14 -fno-common -fexceptions
MODELLIB                  = runADMM.a

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          Xcode with Clang | gmake (64-bit Mac)
# Supported Version(s):    
# ToolchainInfo Version:   2023a
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# C_STANDARD_OPTS
# CPP_STANDARD_OPTS

#-----------
# MACROS
#-----------

ARCHS             = x86_64
XCODE_SDK_VER     = $(shell perl $(MATLAB_ROOT)/rtw/c/tools/macsdkver.pl)
XCODE_SDK         = MacOSX$(XCODE_SDK_VER).sdk
XCODE_DEVEL_DIR   = $(shell xcode-select -print-path)
XCODE_SDK_ROOT    = $(XCODE_DEVEL_DIR)/Platforms/MacOSX.platform/Developer/SDKs/$(XCODE_SDK)

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: Clang C Compiler
CC = xcrun clang

# Linker: Clang Linker
LD = xcrun clang++

# C++ Compiler: Clang C++ Compiler
CPP = xcrun clang++

# C++ Linker: Clang C++ Linker
CPP_LD = xcrun clang++

# Archiver: Clang Archiver
AR = xcrun ar

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%/bin/maci64
MAKE = "$(MAKE_PATH)/gmake"


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -g
C_OUTPUT_FLAG       = -o
LDDEBUG             = -g
OUTPUT_FLAG         = -o
CPPDEBUG            = -g
CPP_OUTPUT_FLAG     = -o
CPPLDDEBUG          = -g
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  = @rm -f
ECHO                = @echo
MV                  = @mv
RUN                 =

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = ruvs
CFLAGS               = -c -isysroot $(XCODE_SDK_ROOT) -arch $(ARCHS) $(C_STANDARD_OPTS) -mmacosx-version-min=10.15 \
                       -O3
CPPFLAGS             = -c -isysroot $(XCODE_SDK_ROOT) -arch $(ARCHS) $(CPP_STANDARD_OPTS) -mmacosx-version-min=10.15 \
                       -O3
CPP_LDFLAGS          = -arch $(ARCHS) -isysroot $(XCODE_SDK_ROOT) -Wl,-rpath,@executable_path -Wl,-rpath,@executable_path/$(RELATIVE_PATH_TO_ANCHOR)
CPP_SHAREDLIB_LDFLAGS  = -arch $(ARCHS)  \
                         -dynamiclib -install_name @rpath/$(notdir $(PRODUCT)) -isysroot $(XCODE_SDK_ROOT) \
                         -Wl,$(LD_NAMESPACE) $(LD_UNDEFS)
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = -arch $(ARCHS) -isysroot $(XCODE_SDK_ROOT) -Wl,-rpath,@executable_path -Wl,-rpath,@executable_path/$(RELATIVE_PATH_TO_ANCHOR)
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -arch $(ARCHS)  \
                       -dynamiclib -install_name @rpath/$(notdir $(PRODUCT)) -isysroot $(XCODE_SDK_ROOT) \
                       -Wl,$(LD_NAMESPACE) $(LD_UNDEFS)



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = ./runADMM.a
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR)/codegen/lib/runADMM -I$(START_DIR) -I$(MATLAB_ROOT)/extern/include

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_CUSTOM = 
DEFINES_STANDARD = -DMODEL=runADMM

DEFINES = $(DEFINES_CUSTOM) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/codegen/lib/runADMM/runADMM_data.c $(START_DIR)/codegen/lib/runADMM/rt_nonfinite.c $(START_DIR)/codegen/lib/runADMM/rtGetNaN.c $(START_DIR)/codegen/lib/runADMM/rtGetInf.c $(START_DIR)/codegen/lib/runADMM/runADMM_initialize.c $(START_DIR)/codegen/lib/runADMM/runADMM_terminate.c $(START_DIR)/codegen/lib/runADMM/runADMM.c $(START_DIR)/codegen/lib/runADMM/sum.c $(START_DIR)/codegen/lib/runADMM/ADMM.c $(START_DIR)/codegen/lib/runADMM/combineVectorElements.c $(START_DIR)/codegen/lib/runADMM/norm.c $(START_DIR)/codegen/lib/runADMM/xnrm2.c $(START_DIR)/codegen/lib/runADMM/conv2AXPYValidCMP.c $(START_DIR)/codegen/lib/runADMM/svd.c $(START_DIR)/codegen/lib/runADMM/svd1.c $(START_DIR)/codegen/lib/runADMM/xzsvdc.c $(START_DIR)/codegen/lib/runADMM/eval_obj.c $(START_DIR)/codegen/lib/runADMM/estimate_W.c $(START_DIR)/codegen/lib/runADMM/constructScaleMats.c $(START_DIR)/codegen/lib/runADMM/checkQuadrics.c $(START_DIR)/codegen/lib/runADMM/nchoosek.c $(START_DIR)/codegen/lib/runADMM/squeeze.c $(START_DIR)/codegen/lib/runADMM/kron.c $(START_DIR)/codegen/lib/runADMM/constructDetMats.c $(START_DIR)/codegen/lib/runADMM/repelem.c $(START_DIR)/codegen/lib/runADMM/repmat.c $(START_DIR)/codegen/lib/runADMM/find.c $(START_DIR)/codegen/lib/runADMM/prod.c $(START_DIR)/codegen/lib/runADMM/mtimes.c $(START_DIR)/codegen/lib/runADMM/xaxpy.c $(START_DIR)/codegen/lib/runADMM/xrotg.c $(START_DIR)/codegen/lib/runADMM/triu.c $(START_DIR)/codegen/lib/runADMM/sign.c $(START_DIR)/codegen/lib/runADMM/sumprod.c $(START_DIR)/codegen/lib/runADMM/div.c $(START_DIR)/codegen/lib/runADMM/conv2AXPY.c $(START_DIR)/codegen/lib/runADMM/s3.c $(START_DIR)/codegen/lib/runADMM/runADMM_emxutil.c $(START_DIR)/codegen/lib/runADMM/runADMM_emxAPI.c $(START_DIR)/codegen/lib/runADMM/runADMM_rtwutil.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = runADMM_data.o rt_nonfinite.o rtGetNaN.o rtGetInf.o runADMM_initialize.o runADMM_terminate.o runADMM.o sum.o ADMM.o combineVectorElements.o norm.o xnrm2.o conv2AXPYValidCMP.o svd.o svd1.o xzsvdc.o eval_obj.o estimate_W.o constructScaleMats.o checkQuadrics.o nchoosek.o squeeze.o kron.o constructDetMats.o repelem.o repmat.o find.o prod.o mtimes.o xaxpy.o xrotg.o triu.o sign.o sumprod.o div.o conv2AXPY.o s3.o runADMM_emxutil.o runADMM_emxAPI.o runADMM_rtwutil.o

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS =  -L"$(MATLAB_ROOT)/sys/os/maci64" -lm -liomp5

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_OPTS = -Xpreprocessor -fopenmp -I/Applications/MATLAB_R2023a.app/toolbox/eml/externalDependency/omp/maci64/include -DOpenMP_omp_LIBRARY=/Applications/MATLAB_R2023a.app/sys/os/maci64/libiomp5.dylib
CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_OPTS) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_OPTS = -Xpreprocessor -fopenmp -I/Applications/MATLAB_R2023a.app/toolbox/eml/externalDependency/omp/maci64/include -DOpenMP_omp_LIBRARY=/Applications/MATLAB_R2023a.app/sys/os/maci64/libiomp5.dylib
CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CPPFLAGS += $(CPPFLAGS_OPTS) $(CPPFLAGS_BASIC)

#---------------
# C++ Linker
#---------------

CPP_LDFLAGS_ = -Wl,-rpath,$(MATLAB_ROOT)/sys/os/maci64

CPP_LDFLAGS += $(CPP_LDFLAGS_)

#------------------------------
# C++ Shared Library Linker
#------------------------------

CPP_SHAREDLIB_LDFLAGS_ = -Wl,-rpath,$(MATLAB_ROOT)/sys/os/maci64

CPP_SHAREDLIB_LDFLAGS += $(CPP_SHAREDLIB_LDFLAGS_)

#-----------
# Linker
#-----------

LDFLAGS_ = -Wl,-rpath,$(MATLAB_ROOT)/sys/os/maci64

LDFLAGS += $(LDFLAGS_)

#--------------------------
# Shared Library Linker
#--------------------------

SHAREDLIB_LDFLAGS_ = -Wl,-rpath,$(MATLAB_ROOT)/sys/os/maci64

SHAREDLIB_LDFLAGS += $(SHAREDLIB_LDFLAGS_)

###########################################################################
## INLINED COMMANDS
###########################################################################

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


prebuild : 


download : $(PRODUCT)


execute : download


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@echo "### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS)  $(PRODUCT) $(OBJS)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.o : %.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : %.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/lib/runADMM/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/lib/runADMM/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


runADMM_data.o : $(START_DIR)/codegen/lib/runADMM/runADMM_data.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rt_nonfinite.o : $(START_DIR)/codegen/lib/runADMM/rt_nonfinite.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetNaN.o : $(START_DIR)/codegen/lib/runADMM/rtGetNaN.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetInf.o : $(START_DIR)/codegen/lib/runADMM/rtGetInf.c
	$(CC) $(CFLAGS) -o "$@" "$<"


runADMM_initialize.o : $(START_DIR)/codegen/lib/runADMM/runADMM_initialize.c
	$(CC) $(CFLAGS) -o "$@" "$<"


runADMM_terminate.o : $(START_DIR)/codegen/lib/runADMM/runADMM_terminate.c
	$(CC) $(CFLAGS) -o "$@" "$<"


runADMM.o : $(START_DIR)/codegen/lib/runADMM/runADMM.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sum.o : $(START_DIR)/codegen/lib/runADMM/sum.c
	$(CC) $(CFLAGS) -o "$@" "$<"


ADMM.o : $(START_DIR)/codegen/lib/runADMM/ADMM.c
	$(CC) $(CFLAGS) -o "$@" "$<"


combineVectorElements.o : $(START_DIR)/codegen/lib/runADMM/combineVectorElements.c
	$(CC) $(CFLAGS) -o "$@" "$<"


norm.o : $(START_DIR)/codegen/lib/runADMM/norm.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xnrm2.o : $(START_DIR)/codegen/lib/runADMM/xnrm2.c
	$(CC) $(CFLAGS) -o "$@" "$<"


conv2AXPYValidCMP.o : $(START_DIR)/codegen/lib/runADMM/conv2AXPYValidCMP.c
	$(CC) $(CFLAGS) -o "$@" "$<"


svd.o : $(START_DIR)/codegen/lib/runADMM/svd.c
	$(CC) $(CFLAGS) -o "$@" "$<"


svd1.o : $(START_DIR)/codegen/lib/runADMM/svd1.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xzsvdc.o : $(START_DIR)/codegen/lib/runADMM/xzsvdc.c
	$(CC) $(CFLAGS) -o "$@" "$<"


eval_obj.o : $(START_DIR)/codegen/lib/runADMM/eval_obj.c
	$(CC) $(CFLAGS) -o "$@" "$<"


estimate_W.o : $(START_DIR)/codegen/lib/runADMM/estimate_W.c
	$(CC) $(CFLAGS) -o "$@" "$<"


constructScaleMats.o : $(START_DIR)/codegen/lib/runADMM/constructScaleMats.c
	$(CC) $(CFLAGS) -o "$@" "$<"


checkQuadrics.o : $(START_DIR)/codegen/lib/runADMM/checkQuadrics.c
	$(CC) $(CFLAGS) -o "$@" "$<"


nchoosek.o : $(START_DIR)/codegen/lib/runADMM/nchoosek.c
	$(CC) $(CFLAGS) -o "$@" "$<"


squeeze.o : $(START_DIR)/codegen/lib/runADMM/squeeze.c
	$(CC) $(CFLAGS) -o "$@" "$<"


kron.o : $(START_DIR)/codegen/lib/runADMM/kron.c
	$(CC) $(CFLAGS) -o "$@" "$<"


constructDetMats.o : $(START_DIR)/codegen/lib/runADMM/constructDetMats.c
	$(CC) $(CFLAGS) -o "$@" "$<"


repelem.o : $(START_DIR)/codegen/lib/runADMM/repelem.c
	$(CC) $(CFLAGS) -o "$@" "$<"


repmat.o : $(START_DIR)/codegen/lib/runADMM/repmat.c
	$(CC) $(CFLAGS) -o "$@" "$<"


find.o : $(START_DIR)/codegen/lib/runADMM/find.c
	$(CC) $(CFLAGS) -o "$@" "$<"


prod.o : $(START_DIR)/codegen/lib/runADMM/prod.c
	$(CC) $(CFLAGS) -o "$@" "$<"


mtimes.o : $(START_DIR)/codegen/lib/runADMM/mtimes.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xaxpy.o : $(START_DIR)/codegen/lib/runADMM/xaxpy.c
	$(CC) $(CFLAGS) -o "$@" "$<"


xrotg.o : $(START_DIR)/codegen/lib/runADMM/xrotg.c
	$(CC) $(CFLAGS) -o "$@" "$<"


triu.o : $(START_DIR)/codegen/lib/runADMM/triu.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sign.o : $(START_DIR)/codegen/lib/runADMM/sign.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sumprod.o : $(START_DIR)/codegen/lib/runADMM/sumprod.c
	$(CC) $(CFLAGS) -o "$@" "$<"


div.o : $(START_DIR)/codegen/lib/runADMM/div.c
	$(CC) $(CFLAGS) -o "$@" "$<"


conv2AXPY.o : $(START_DIR)/codegen/lib/runADMM/conv2AXPY.c
	$(CC) $(CFLAGS) -o "$@" "$<"


s3.o : $(START_DIR)/codegen/lib/runADMM/s3.c
	$(CC) $(CFLAGS) -o "$@" "$<"


runADMM_emxutil.o : $(START_DIR)/codegen/lib/runADMM/runADMM_emxutil.c
	$(CC) $(CFLAGS) -o "$@" "$<"


runADMM_emxAPI.o : $(START_DIR)/codegen/lib/runADMM/runADMM_emxAPI.c
	$(CC) $(CFLAGS) -o "$@" "$<"


runADMM_rtwutil.o : $(START_DIR)/codegen/lib/runADMM/runADMM_rtwutil.c
	$(CC) $(CFLAGS) -o "$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### CPPFLAGS = $(CPPFLAGS)"
	@echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files ..."
	$(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(ECHO) "### Deleted all derived files."


