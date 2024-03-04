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
  const char_T *data[7] = {
      "789ced574f8fd240142f1b349bcdaa9c3c9b6ce2c5608122610f1e5858024b59a4e0ff18"
      "2c65968edb76a0d322908d89c6bbdfc12fe177f0a4d9a3973d68e2a7"
      "30524a293469200b4c03f41dfafaf2ebccafef4de737af54205f0c5014759b32edef81e9"
      "6f8de2d0c8ef50d3e6c403237fd3115b76830a4e8db3f02f232f2045",
      "035dcd0c145e06e3910d24438557b46aaf0528156024754063889c410954a10c2a93c1a9"
      "11c9d909681c1890719f1681705ed1654a15b1fd86d26460d7c325df"
      "e09cf5f8e8528f90037f7dfc867e8a818a69d4871a9265486790a0cb40d1305d4c55d9d4"
      "119d834d11a8f74a6a6370adf40451450aecf31a440acd4b4d505779",
      "28d40695c4dae06e30b0168987234c381689c5ed07c2c26076a48425a8004cabba92ca14"
      "8b0f6547de6f17cc3be888edbc4d24cfb19565f2b97d77a111322889"
      "2e6836dfd5827c1f5cf9a671afd6d5a8afb1a8b3ea7b67ce7c9dde7e7e77e8ff5dfe196e"
      "59527c3f7fd7ef93e4b3cc2bbeaecb7cf37eaf775df8420e3c917ed1",
      "3eec72cdc37e1b320991d59282543fb6dfe3c90c9e59ef41b9c4a4e6bf7219bf6dfb7e59"
      "3a6e1c1e86f7757c35eb691dcea47427fa83ac8e7ffdb6ff80249f65"
      "9baee3f84888a6f2c9b2da6c83189beceb09ccc533be8eafcbbe5fb68eef3a623b5f1301"
      "1d5eaaa1fa3baf747cd1ffac4fae7cd3b857eb69d5d7fad122a53fdf",
      "957da27a6ed9b6f091d2f30adb95992427f21815d26cf79156289d9fe53647cffdfd7fbd"
      "bc771cb19db7896066b97cb374bd81f4ba0496774e5fb8f24de35ead"
      "2b66cc1525a53f178f2f1b24f92cdb163e527a7e92785692cb89961e7ddf3f7d99113bf8"
      "5539ebf7e76bdb9fb716cc776f46be160eb006655e03b5e766bcaefd",
      "fa6757be69dcb3f37a5c67b2fabe17fae5f7eb2be423a5ef5c021644a6878b69b690cf15"
      "b99324c3a1ece6e8bbbfffaf97b7dfaf9be6f7ebabe1b36c5bf8fc7e"
      "7db1f9ff034fa6ead0",
      ""};
  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(&data[0], 9216U, &nameCaptureInfo);
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
                emlrtMxCreateDoubleScalar(3.0));
  emlrtSetField(xEntryPoints, 0, "ConstantInputs", xInputs);
  emlrtSetField(
      xEntryPoints, 0, "FullPath",
      emlrtMxCreateString("/Users/ozitommi/Documents/MATLAB/Higher Order "
                          "Sychronization/algebraic_constraints_04-03-2024/"
                          "algebraic-common-lines/runADMM.m"));
  emlrtSetField(xEntryPoints, 0, "TimeStamp",
                emlrtMxCreateDoubleScalar(739315.55803240743));
  xResult =
      emlrtCreateStructMatrix(1, 1, 7, (const char_T **)&propFieldName[0]);
  emlrtSetField(xResult, 0, "Version",
                emlrtMxCreateString("9.14.0.2206163 (R2023a)"));
  emlrtSetField(xResult, 0, "ResolvedFunctions",
                (mxArray *)emlrtMexFcnResolvedFunctionsInfo());
  emlrtSetField(xResult, 0, "Checksum",
                emlrtMxCreateString("ZjKErGDi8uvzyS6Ljg0x7G"));
  emlrtSetField(xResult, 0, "EntryPoints", xEntryPoints);
  return xResult;
}

/* End of code generation (_coder_runADMM_info.c) */
