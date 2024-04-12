  explicit TabStripDummyDelegate(TabContentsWrapper* dummy)
      : dummy_contents_(dummy), can_close_(true), run_unload_(false) {}
