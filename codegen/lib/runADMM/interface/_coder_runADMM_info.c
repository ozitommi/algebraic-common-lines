/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_runADMM_info.c
 *
 * Code generation for function 'runADMM'
 *
 */

/* Include files */
#include "_coder_runADMM_info.h"
#include "emlrt.h"
#include "tmwtypes.h"

/* Function Declarations */
static const mxArray *emlrtMexFcnResolvedFunctionsInfo(void);

/* Function Definitions */
static const mxArray *emlrtMexFcnResolvedFunctionsInfo(void)
{
  const mxArray *nameCaptureInfo;
  const char_T *data[9] = {
      "789ced5a4d73d240184e6bed74d42a7e4c0f8e07af1e5abe697bf000a415ca37b4d4e238"
      "348405024996e6a3858cce78f1ec8ff0d28be3df703c39a387fe077f"
      "81e34520049a75223881a50d790f6cde79923cfbbecb3ebb791362219a582008e22ea1da"
      "f9b6daaef67d47bf5d24f486e20bfdf616e26b769358d25da7e11ffa",
      "2d0d7909b424d5e1290e0cae2c438ee1295eda6f3701210011b2a7a0dc432a0c0bf6190e"
      "e42e3bc9aec7ed5e82064e17ea1e876b806ee4648e106ae2b087ec65"
      "67908f6f06f12e8d998fba413e1c08fe6ae7b5f3400482e8840a23418e639c24a4650ef0"
      "92e84c04f7e3c19033c2546b40789a12ca9ddf5c9bae099067144a62",
      "20efa4d82a28091443173b9914a5ce51e7c2a2c7b3ee76ad7b5c1eaf5390f92099486c70"
      "faf88e4dc6b784f8c3f854249a8de726c9b76cc8a7229dd0655a1af2"
      "7d31c95735e4d3e3531fbf6e223b83372a8ff7c68c0b6d87e7aff4daf70ffdbd29888bef"
      "c7c5bb6738f9349b155fcbe07ee3fe2fd70cf81c081e384991a142fa",
      "244bb1e97a13fab7b3153eb333ec477a04cfa87e10063eaefbcfdbfc9e942e77d7826e6b"
      "ebb2c971eb2faab874e4f6325e5dfefd2212c0c9a799d575b9e0e19a"
      "fe8ccb0d8f5ed6f20a8c8b659975856c5dbe72f37bc2babc82f8c3b854049c526c1196ea"
      "b3d265b3cf3b0d433e3d3ef571d312d97fe0c1a5275ff93b58f559b3",
      "79e1c3a5cfb9788bf36e656b940863e178cb2fc5528d4ac43afa3caff37cdcf816117f18"
      "9f8a885e62a27ca374ba0ce5120b26b7be02c42790f3347ceae3277a"
      "7b23874b4fde3cffde2b1ece8b5ee2e6c3a5cf7b817c8acb049ab2fb4c491e91b553b190"
      "d925ada3cf56dd3f374dc665f47ec181e04094188e9240f150f5afeb",
      "7e9a33e4d3e3d35f670709c5aad76fefe3ad77fcfa7cc381934f33abeb7536c0c46adeb6"
      "9808c763d14822bbb7e5cdc25debe8f5bcce737b3fad9abd9fc6c3a7"
      "d9bcf0d9fbe9c9dcdfac3e5ff5ef38ccfe4f1e8c884fc3d55e75b6b8399a62418292447d"
      "3f8e4df6e37f75fbc2249f6cc8a7c7a73eae7f2716ab8eb3c52776dd",
      "7a8a7cb8747cb3146a934a3a7992f265cfc2a1c3835c702f13b675fcbae8b8d9fac82ae2"
      "a3f16938ddfd063223536581a1456276fa6d763c9b884f20e769f8f4"
      "f5fb724237385c3a73eec35b1ff9b8f2e8314e3ecdacaedb75aa5d25d9787e33ad508564"
      "ca1f8872f52d5bb7affd3cb7eb23aad9f5113c7c9acd0b9f5d1f99cc",
      "fded7df5bfe333caa70369078ff12490ba0ff1b37aef68b62e22223e819ca7e1f8ea22fd"
      "8462fe9e6feda70febfeba92f8e4c3c9a799d5f55b89910a4f930da5"
      "148ec200ed4ee50350b1c0f7d67f0009112829",
      ""};
  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(&data[0], 14784U, &nameCaptureInfo);
  return nameCaptureInfo;
}

mxArray *emlrtMexFcnProperties(void)
{
  mxArray *xEntryPoints;
  mxArray *xInputs;
  mxArray *xResult;
  const char_T *propFieldName[7] = {
      "Version",      "ResolvedFunctions", "Checksum",    "EntryPoints",
      "CoverageInfo", "IsPolymorphic",     "PropertyList"};
  const char_T *epFieldName[6] = {
      "Name",           "NumberOfInputs", "NumberOfOutputs",
      "ConstantInputs", "FullPath",       "TimeStamp"};
  xEntryPoints =
      emlrtCreateStructMatrix(1, 1, 6, (const char_T **)&epFieldName[0]);
  xInputs = emlrtCreateLogicalMatrix(1, 1);
  emlrtSetField(xEntryPoints, 0, "Name", emlrtMxCreateString("runADMM"));
  emlrtSetField(xEntryPoints, 0, "NumberOfInputs",
                emlrtMxCreateDoubleScalar(1.0));
  emlrtSetField(xEntryPoints, 0, "NumberOfOutputs",
                emlrtMxCreateDoubleScalar(4.0));
  emlrtSetField(xEntryPoints, 0, "ConstantInputs", xInputs);
  emlrtSetField(
      xEntryPoints, 0, "FullPath",
      emlrtMxCreateString(
          "/Users/ozitommi/Documents/MATLAB/Higher Order "
          "Sychronization/algebraic_constraints_22-10-2023/runADMM.m"));
  emlrtSetField(xEntryPoints, 0, "TimeStamp",
                emlrtMxCreateDoubleScalar(739181.56043981481));
  xResult =
      emlrtCreateStructMatrix(1, 1, 7, (const char_T **)&propFieldName[0]);
  emlrtSetField(xResult, 0, "Version",
                emlrtMxCreateString("9.14.0.2206163 (R2023a)"));
  emlrtSetField(xResult, 0, "ResolvedFunctions",
                (mxArray *)emlrtMexFcnResolvedFunctionsInfo());
  emlrtSetField(xResult, 0, "Checksum",
                emlrtMxCreateString("FbHIMMbjtCRjYRv62Zh0kD"));
  emlrtSetField(xResult, 0, "EntryPoints", xEntryPoints);
  return xResult;
}

/* End of code generation (_coder_runADMM_info.c) */
