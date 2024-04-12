void LogServerError(const CommitResponse_EntryResponse& res) {
  if (res.has_error_message())
    LOG(WARNING) << "  " << res.error_message();
  else
    LOG(WARNING) << "  No detailed error message returned from server";
}
