void BrowserView::UpdateAcceleratorMetrics(
    const ui::Accelerator& accelerator, int command_id) {
  const ui::KeyboardCode key_code = accelerator.key_code();
  if (command_id == IDC_HELP_PAGE_VIA_KEYBOARD && key_code == ui::VKEY_F1)
    content::RecordAction(UserMetricsAction("ShowHelpTabViaF1"));

  if (command_id == IDC_BOOKMARK_PAGE)
    UMA_HISTOGRAM_ENUMERATION("Bookmarks.EntryPoint",
                              bookmark_utils::ENTRY_POINT_ACCELERATOR,
                              bookmark_utils::ENTRY_POINT_LIMIT);

#if defined(OS_CHROMEOS)
  switch (command_id) {
    case IDC_BACK:
      if (key_code == ui::VKEY_BACK)
        content::RecordAction(UserMetricsAction("Accel_Back_Backspace"));
      else if (key_code == ui::VKEY_F1)
        content::RecordAction(UserMetricsAction("Accel_Back_F1"));
      else if (key_code == ui::VKEY_LEFT)
        content::RecordAction(UserMetricsAction("Accel_Back_Left"));
      break;
    case IDC_FORWARD:
      if (key_code == ui::VKEY_BACK)
        content::RecordAction(UserMetricsAction("Accel_Forward_Backspace"));
      else if (key_code == ui::VKEY_F2)
        content::RecordAction(UserMetricsAction("Accel_Forward_F2"));
      else if (key_code == ui::VKEY_RIGHT)
        content::RecordAction(UserMetricsAction("Accel_Forward_Right"));
      break;
    case IDC_RELOAD:
    case IDC_RELOAD_IGNORING_CACHE:
      if (key_code == ui::VKEY_R)
        content::RecordAction(UserMetricsAction("Accel_Reload_R"));
      else if (key_code == ui::VKEY_F3)
        content::RecordAction(UserMetricsAction("Accel_Reload_F3"));
      break;
    case IDC_FULLSCREEN:
      if (key_code == ui::VKEY_F4)
        content::RecordAction(UserMetricsAction("Accel_Fullscreen_F4"));
      break;
    case IDC_FOCUS_LOCATION:
      if (key_code == ui::VKEY_D)
        content::RecordAction(UserMetricsAction("Accel_FocusLocation_D"));
      else if (key_code == ui::VKEY_L)
        content::RecordAction(UserMetricsAction("Accel_FocusLocation_L"));
      break;
    case IDC_FOCUS_SEARCH:
      if (key_code == ui::VKEY_E)
        content::RecordAction(UserMetricsAction("Accel_FocusSearch_E"));
      else if (key_code == ui::VKEY_K)
        content::RecordAction(UserMetricsAction("Accel_FocusSearch_K"));
      break;
    default:
      break;
  }
#endif
}
