  void FocusInputInFrame(RenderFrameHostImpl* frame) {
    ASSERT_TRUE(ExecuteScript(frame, "window.focus(); input.focus();"));
  }
