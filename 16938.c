  virtual void SetUpOnMainThread() {
    ASSERT_TRUE(ui_test_utils::BringBrowserWindowToFront(browser()));
    ASSERT_NO_FATAL_FAILURE(SetupComponents());
    chrome::FocusLocationBar(browser());
    ViewID location_bar_focus_view_id = VIEW_ID_LOCATION_BAR;
#if defined(USE_AURA)
    location_bar_focus_view_id = VIEW_ID_OMNIBOX;
#endif
    ASSERT_TRUE(ui_test_utils::IsViewFocused(browser(),
                                             location_bar_focus_view_id));
  }
