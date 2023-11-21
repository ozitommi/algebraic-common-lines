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
      "789ced5acb6ed3401475ab52554021b0e80a21f628e4d5a405c422895b35cdfbd19406a1"
      "d471a68d53db93da4e9b58050984044248fc06dfc2961fe88205121b"
      "3e81b88ee3d86894522763359959647c753c73e6dec91cdfdc989a4ba4e7288aba43e9ed"
      "d373bd5feedb9e7e3f4f599b1d9febf7376db6d16e500b967106feb5",
      "dfb350544047d10d9111c060641d0a9cc8884aa9db02940464c89f80fa0572c0f1a0c409"
      "a0386c64344bd81c8206860669d7f106608f8a6d81921ab2b9427ed8"
      "18c4e317c2df854bc6e31d221e1e1bfe6ae3b56f470692ec832aa74041e07c3464db0210"
      "15d9978e9652d1986f8b3b6c00e95156aaf73e8b5db6214191531985",
      "83a28fe10f414d6238b6da8ba4acf4ae7a03abc19037e0f706fdc190798397edcd0e452f"
      "cf8940f6496d314aa7d34f049bdffb0efd5eb0d9a6df3a9228a48ae3"
      "e45b44f2e9482f246d5631f9ce1df2bd45f25971b7f6558bafb6a9a3e27bf792feda7bf3"
      "fea58b9efdf9ece2c8e2e2db7f5c7a8893cf686ef17510f35df6fbba",
      "82e0f3d8f0c871968e5572c70586cf355b30fcb47020e637cc75e446f08c5a0785b071cd"
      "7f8e183f6be77e5c3aae3d3cb49ee8f864f6d37838e3d29d5b8b61ac"
      "3a6eb459e1c3a5e395a0d00ae7fd01b8f7b25156614aaeb7797f8ce8f87539f7e3d6f125"
      "9b6dfaab23e084e1abb0d6744bc79dfece7a8fe4b3e26eeda7115fe3",
      "87162efdf92ede267a3e413e5c7a5e4c7584d07aa1c1c830194f75c24a327b74b0353d7a"
      "4eceffd5fc9eb7d9a6df3a2287c6cb374ad7ebb05de3c1f89ed36748"
      "3e2beed6beca217d4771e9cfd98b1f759c7c469b153e5c7abe1d2967857ca4d50e9caa99"
      "3dba712257f29bf4f4e8f93962fcb4e6e72d87fea2fe37f1d870202b",
      "9cc028a0baabdbd7355fff80e4b3e2ae3daf0771c6abef6fee91facb24f970e97b21c225"
      "1ba1ae9c8ea79289ad74617b3d54809bd3a3efe4fc5fcd6f92afeb8d"
      "e4eb93e133daacf0917c7d3cf3cfea7b2e4ebf3ff747f86de0fa6a7b2974916578906614"
      "d9ba8e7d87ebf85f9dffe390ef0b92cf8abbb5dfffc61bafeef3d507",
      "248f9f201f2edd5fabc5bab49acb1c67570ba7f1d8ee4e31ba9d8f13ddbfeebaefb45eb3"
      "6cb3ed7e1b38abbd6b9a6f3375896365ca3dbd77bacf1f917c56dc35"
      "bd1f8e736fb771e9d2b75552af99241f2e9d6f32dd439a4f95d7722a53c964c39184d05c"
      "273a3fb5e79fd46bf446ea35c6fda45e83838fd46bc6333fc9dbafe6",
      "372ace1e5b3fa81fd040d1aa076efdcfeab44ef319c967c55dafd3f4e38cfbfdc895dfab"
      "247f9f201f2ebd5793b42ab2f4915a8b2760840d64cb11a84ec1fbee"
      "7f015d75d697",
      ""};
  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(&data[0], 15264U, &nameCaptureInfo);
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
      emlrtMxCreateString("/Users/ozitommi/Documents/MATLAB/Higher Order "
                          "Sychronization/algebraic_constraints_23-10-2023/"
                          "algebraic-common-lines/runADMM.m"));
  emlrtSetField(xEntryPoints, 0, "TimeStamp",
                emlrtMxCreateDoubleScalar(739185.97535879631));
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
