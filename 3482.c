const gfx::VectorIcon& AuthenticatorBlePinEntrySheetModel::GetStepIllustration(
    ImageColorScheme color_scheme) const {
  return color_scheme == ImageColorScheme::kDark ? kWebauthnBlePinDarkIcon
                                                 : kWebauthnBlePinIcon;
}
