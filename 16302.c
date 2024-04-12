ExtensionFunction::ResponseAction WindowsRemoveFunction::Run() {
  std::unique_ptr<windows::Remove::Params> params(
      windows::Remove::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params);

  Browser* browser = nullptr;
  std::string error;
  if (!windows_util::GetBrowserFromWindowID(this, params->window_id,
                                            WindowController::kNoWindowFilter,
                                            &browser, &error)) {
    return RespondNow(Error(error));
  }

#if defined(OS_CHROMEOS)
  if (ash::IsWindowTrustedPinned(browser->window()) &&
      !ExtensionHasLockedFullscreenPermission(extension())) {
    return RespondNow(
        Error(tabs_constants::kMissingLockWindowFullscreenPrivatePermission));
  }
#endif

  WindowController* controller = browser->extension_window_controller();
  WindowController::Reason reason;
  if (!controller->CanClose(&reason)) {
    return RespondNow(Error(reason == WindowController::REASON_NOT_EDITABLE
                                ? tabs_constants::kTabStripNotEditableError
                                : kUnknownErrorDoNotUse));
  }
  controller->window()->Close();
  return RespondNow(NoArguments());
}
