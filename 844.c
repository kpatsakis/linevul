ExtensionFunction::ResponseAction UsbGetUserSelectedDevicesFunction::Run() {
  scoped_ptr<extensions::core_api::usb::GetUserSelectedDevices::Params>
      parameters = GetUserSelectedDevices::Params::Create(*args_);
  EXTENSION_FUNCTION_VALIDATE(parameters.get());

  if (!user_gesture()) {
    return RespondNow(OneArgument(new base::ListValue()));
  }

  bool multiple = false;
  if (parameters->options.multiple) {
    multiple = *parameters->options.multiple;
  }

  std::vector<UsbDeviceFilter> filters;
  if (parameters->options.filters) {
    filters.resize(parameters->options.filters->size());
    for (size_t i = 0; i < parameters->options.filters->size(); ++i) {
      ConvertDeviceFilter(*parameters->options.filters->at(i).get(),
                          &filters[i]);
    }
  }

  prompt_ = ExtensionsAPIClient::Get()->CreateDevicePermissionsPrompt(
      GetAssociatedWebContents());
  if (!prompt_) {
    return RespondNow(Error(kErrorNotSupported));
  }

  prompt_->AskForUsbDevices(
      extension(), browser_context(), multiple, filters,
      base::Bind(&UsbGetUserSelectedDevicesFunction::OnDevicesChosen, this));
  return RespondLater();
}
