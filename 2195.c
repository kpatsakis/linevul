const gfx::VectorIcon& AuthenticatorBleActivateSheetModel::GetStepIllustration(
    ImageColorScheme color_scheme) const {
  return color_scheme == ImageColorScheme::kDark ? kWebauthnBleTapDarkIcon
                                                 : kWebauthnBleTapIcon;
}
