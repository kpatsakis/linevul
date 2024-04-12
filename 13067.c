  void WaitForOneCapturedBuffer() {
    base::RunLoop run_loop;

    EXPECT_CALL(*this, DoOnBufferReady(_))
        .Times(AnyNumber())
        .WillOnce(ExitMessageLoop(task_runner_, run_loop.QuitClosure()))
        .RetiresOnSaturation();
    run_loop.Run();
  }
