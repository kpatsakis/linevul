base::string16 AuthenticatorWelcomeSheetModel::GetStepTitle() const {
  return l10n_util::GetStringFUTF16(IDS_WEBAUTHN_WELCOME_SCREEN_TITLE,
                                    GetRelyingPartyIdString(dialog_model()));
}
