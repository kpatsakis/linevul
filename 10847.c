void Plugin::BitcodeDidTranslateContinuation(int32_t pp_error) {
  ErrorInfo error_info;
  bool was_successful = LoadNaClModuleContinuationIntern(&error_info);

  NaClLog(4, "Entered BitcodeDidTranslateContinuation\n");
  UNREFERENCED_PARAMETER(pp_error);
  if (was_successful) {
    ReportLoadSuccess(LENGTH_IS_NOT_COMPUTABLE,
                      kUnknownBytes,
                      kUnknownBytes);
  } else {
    ReportLoadError(error_info);
  }
}
