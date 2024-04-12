 virtual void SetUp() {
 AllocationTestHarness::SetUp();
      pipe(pipefd);
      done = semaphore_new(0);
 }
