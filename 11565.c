  void WaitForCopySourceReady() {
    while (!GetRenderWidgetHostViewPort()->IsSurfaceAvailableForCopy())
      GiveItSomeTime();
  }
