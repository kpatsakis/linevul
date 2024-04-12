void CloseHandlesAndTerminateProcess(PROCESS_INFORMATION* process_information) {
  if (process_information->hThread) {
    CloseHandle(process_information->hThread);
    process_information->hThread = NULL;
  }

  if (process_information->hProcess) {
    TerminateProcess(process_information->hProcess, CONTROL_C_EXIT);
    CloseHandle(process_information->hProcess);
    process_information->hProcess = NULL;
  }
}
