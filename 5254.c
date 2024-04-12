bool ConnectToExecutionServer(uint32 session_id,
                              base::win::ScopedHandle* pipe_out) {
  string16 pipe_name;

  FilePath winsta_path(base::GetNativeLibraryName(UTF8ToUTF16("winsta")));
  base::ScopedNativeLibrary winsta(winsta_path);
  if (winsta.is_valid()) {
    PWINSTATIONQUERYINFORMATIONW win_station_query_information =
        static_cast<PWINSTATIONQUERYINFORMATIONW>(
            winsta.GetFunctionPointer("WinStationQueryInformationW"));
    if (win_station_query_information) {
      wchar_t name[MAX_PATH];
      ULONG name_length;
      if (win_station_query_information(0,
                                        session_id,
                                        kCreateProcessPipeNameClass,
                                        name,
                                        sizeof(name),
                                        &name_length)) {
        pipe_name.assign(name);
      }
    }
  }

  if (pipe_name.empty()) {
    pipe_name = UTF8ToUTF16(
        StringPrintf(kCreateProcessDefaultPipeNameFormat, session_id));
  }

  base::win::ScopedHandle pipe;
  for (int i = 0; i < kPipeConnectMaxAttempts; ++i) {
    pipe.Set(CreateFile(pipe_name.c_str(),
                        GENERIC_READ | GENERIC_WRITE,
                        0,
                        NULL,
                        OPEN_EXISTING,
                        0,
                        NULL));
    if (pipe.IsValid()) {
      break;
    }

    if (GetLastError() != ERROR_PIPE_BUSY) {
      break;
    }

    if (!WaitNamedPipe(pipe_name.c_str(), kPipeBusyWaitTimeoutMs)) {
      break;
    }
  }

  if (!pipe.IsValid()) {
    LOG_GETLASTERROR(ERROR) << "Failed to connect to '" << pipe_name << "'";
    return false;
  }

  *pipe_out = pipe.Pass();
  return true;
}
