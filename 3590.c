AuthenticatorClientPinEntrySheetModel::GetStepIllustration(
    ImageColorScheme color_scheme) const {
  return color_scheme == ImageColorScheme::kDark ? kWebauthnUsbDarkIcon
                                                 : kWebauthnUsbIcon;
}
