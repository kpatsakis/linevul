  void DestroyTabletModeWindowManager() {
    Shell::Get()->tablet_mode_controller()->EnableTabletModeWindowManager(
        false);
    EXPECT_FALSE(tablet_mode_window_manager());
  }
