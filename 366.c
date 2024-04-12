static void monitor_worker_process(int child_pid, const debugger_request_t& request) {
 struct timespec timeout = {.tv_sec = 10, .tv_nsec = 0 };
 if (should_attach_gdb(request)) {
    timeout.tv_sec = INT_MAX;
 }

 sigset_t signal_set;
  sigemptyset(&signal_set);
  sigaddset(&signal_set, SIGCHLD);

 bool kill_worker = false;
 bool kill_target = false;
 bool kill_self = false;

 int status;
 siginfo_t siginfo;
 int signal = TEMP_FAILURE_RETRY(sigtimedwait(&signal_set, &siginfo, &timeout));
 if (signal == SIGCHLD) {
 pid_t rc = waitpid(-1, &status, WNOHANG | WUNTRACED);
 if (rc != child_pid) {
      ALOGE("debuggerd: waitpid returned unexpected pid (%d), committing murder-suicide", rc);

 if (WIFEXITED(status)) {
        ALOGW("debuggerd: pid %d exited with status %d", rc, WEXITSTATUS(status));
 } else if (WIFSIGNALED(status)) {
        ALOGW("debuggerd: pid %d received signal %d", rc, WTERMSIG(status));
 } else if (WIFSTOPPED(status)) {
        ALOGW("debuggerd: pid %d stopped by signal %d", rc, WSTOPSIG(status));
 } else if (WIFCONTINUED(status)) {
        ALOGW("debuggerd: pid %d continued", rc);
 }

      kill_worker = true;
      kill_target = true;
      kill_self = true;
 } else if (WIFSIGNALED(status)) {
      ALOGE("debuggerd: worker process %d terminated due to signal %d", child_pid, WTERMSIG(status));
      kill_worker = false;
      kill_target = true;
 } else if (WIFSTOPPED(status)) {
      ALOGE("debuggerd: worker process %d stopped due to signal %d", child_pid, WSTOPSIG(status));
      kill_worker = true;
      kill_target = true;
 }
 } else {
    ALOGE("debuggerd: worker process %d timed out", child_pid);
    kill_worker = true;
    kill_target = true;
 }

 if (kill_worker) {
 if (kill(child_pid, SIGKILL) != 0) {
      ALOGE("debuggerd: failed to kill worker process %d: %s", child_pid, strerror(errno));
 } else {
      waitpid(child_pid, &status, 0);
 }
 }

 int exit_signal = SIGCONT;
 if (kill_target && request.action == DEBUGGER_ACTION_CRASH) {
    ALOGE("debuggerd: killing target %d", request.pid);
    exit_signal = SIGKILL;
 } else {
    ALOGW("debuggerd: resuming target %d", request.pid);
 }

 if (kill(request.pid, exit_signal) != 0) {
    ALOGE("debuggerd: failed to send signal %d to target: %s", exit_signal, strerror(errno));
 }

 if (kill_self) {
    stop_signal_sender();
    _exit(1);
 }
}
