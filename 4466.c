int TestOpenThread(DWORD thread_id) {

  HANDLE thread = ::OpenThread(THREAD_QUERY_INFORMATION,
                               FALSE,  // Do not inherit handles.
                               thread_id);

  if (NULL == thread) {
    if (ERROR_ACCESS_DENIED == ::GetLastError()) {
      return SBOX_TEST_DENIED;
    } else {
      return SBOX_TEST_FAILED_TO_EXECUTE_COMMAND;
    }
  } else {
    ::CloseHandle(thread);
    return SBOX_TEST_SUCCEEDED;
  }
}
