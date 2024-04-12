void TestingAutomationProvider::SendOSLevelKeyEventToTab(
    DictionaryValue* args,
    IPC::Message* reply_message) {
  if (SendErrorIfModalDialogActive(this, reply_message))
    return;

  int modifiers, keycode;
  if (!args->GetInteger("keyCode", &keycode)) {
    AutomationJSONReply(this, reply_message)
        .SendError("'keyCode' missing or invalid.");
    return;
  }
  if (!args->GetInteger("modifiers", &modifiers)) {
    AutomationJSONReply(this, reply_message)
        .SendError("'modifiers' missing or invalid.");
    return;
  }

  std::string error;
  Browser* browser;
  WebContents* web_contents;
  if (!GetBrowserAndTabFromJSONArgs(args, &browser, &web_contents, &error)) {
    AutomationJSONReply(this, reply_message).SendError(error);
    return;
  }
  browser->ActivateTabAt(
      browser->GetIndexOfController(&web_contents->GetController()), true);

  BrowserWindow* browser_window = browser->window();
  if (!browser_window) {
    AutomationJSONReply(this, reply_message)
        .SendError("Could not get the browser window");
    return;
  }
  gfx::NativeWindow window = browser_window->GetNativeHandle();
  if (!window) {
    AutomationJSONReply(this, reply_message)
        .SendError("Could not get the browser window handle");
    return;
  }

  bool control = !!(modifiers & automation::kControlKeyMask);
  bool shift = !!(modifiers & automation::kShiftKeyMask);
  bool alt = !!(modifiers & automation::kAltKeyMask);
  bool meta = !!(modifiers & automation::kMetaKeyMask);
  if (!ui_controls::SendKeyPressNotifyWhenDone(
          window, static_cast<ui::KeyboardCode>(keycode),
          control, shift, alt, meta,
          base::Bind(&TestingAutomationProvider::SendSuccessReply, this,
                     reply_message))) {
    AutomationJSONReply(this, reply_message)
        .SendError("Could not send the native key event");
  }
}
