ExtensionFunction::ResponseAction UsbRequestAccessFunction::Run() {
  scoped_ptr<extensions::core_api::usb::RequestAccess::Params> parameters =
      RequestAccess::Params::Create(*args_);
  EXTENSION_FUNCTION_VALIDATE(parameters.get());
  return RespondNow(OneArgument(new base::FundamentalValue(true)));
}
