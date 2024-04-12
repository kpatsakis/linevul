  TestAutoFillManager(TabContents* tab_contents,
                      TestPersonalDataManager* personal_manager)
      : AutoFillManager(tab_contents, personal_manager),
        autofill_enabled_(true) {
    set_metric_logger(new MockAutoFillMetrics);
  }
