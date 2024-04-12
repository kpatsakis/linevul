bool AcceleratorControllerDelegateAura::HandlesAction(
    AcceleratorAction action) {
  switch (action) {
    case DEBUG_TOGGLE_DESKTOP_BACKGROUND_MODE:
    case DEBUG_TOGGLE_DEVICE_SCALE_FACTOR:
    case DEBUG_TOGGLE_ROOT_WINDOW_FULL_SCREEN:
    case DEBUG_TOGGLE_SHOW_DEBUG_BORDERS:
    case DEBUG_TOGGLE_SHOW_FPS_COUNTER:
    case DEBUG_TOGGLE_SHOW_PAINT_RECTS:
    case FOCUS_SHELF:
    case LAUNCH_APP_0:
    case LAUNCH_APP_1:
    case LAUNCH_APP_2:
    case LAUNCH_APP_3:
    case LAUNCH_APP_4:
    case LAUNCH_APP_5:
    case LAUNCH_APP_6:
    case LAUNCH_APP_7:
    case LAUNCH_LAST_APP:
    case MAGNIFY_SCREEN_ZOOM_IN:
    case MAGNIFY_SCREEN_ZOOM_OUT:
    case ROTATE_SCREEN:
    case ROTATE_WINDOW:
    case SCALE_UI_DOWN:
    case SCALE_UI_RESET:
    case SCALE_UI_UP:
    case SHOW_MESSAGE_CENTER_BUBBLE:
    case SHOW_SYSTEM_TRAY_BUBBLE:
    case TAKE_PARTIAL_SCREENSHOT:
    case TAKE_SCREENSHOT:
    case TAKE_WINDOW_SCREENSHOT:
    case UNPIN:
      return true;

#if defined(OS_CHROMEOS)
    case DEBUG_ADD_REMOVE_DISPLAY:
    case DEBUG_TOGGLE_UNIFIED_DESKTOP:
    case DISABLE_GPU_WATCHDOG:
    case LOCK_PRESSED:
    case LOCK_RELEASED:
    case POWER_PRESSED:
    case POWER_RELEASED:
    case SWAP_PRIMARY_DISPLAY:
    case TOGGLE_MIRROR_MODE:
    case TOUCH_HUD_CLEAR:
    case TOUCH_HUD_MODE_CHANGE:
    case TOUCH_HUD_PROJECTION_TOGGLE:
      return true;
#endif

    default:
      break;
  }
  return false;
}
