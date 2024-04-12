blink::WebPushPermissionStatus ToPushPermission(
    ContentSetting content_setting) {
  switch (content_setting) {
    case CONTENT_SETTING_ALLOW:
      return blink::kWebPushPermissionStatusGranted;
    case CONTENT_SETTING_BLOCK:
      return blink::kWebPushPermissionStatusDenied;
    case CONTENT_SETTING_ASK:
      return blink::kWebPushPermissionStatusPrompt;
    default:
      break;
  }
  NOTREACHED();
  return blink::kWebPushPermissionStatusDenied;
}
