  void WaitForDidFirstVisuallyNonEmptyPaint() {
    if (did_fist_visually_non_empty_paint_)
      return;
    base::RunLoop run_loop;
    on_did_first_visually_non_empty_paint_ = run_loop.QuitClosure();
    run_loop.Run();
  }
