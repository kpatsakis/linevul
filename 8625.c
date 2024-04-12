base::string16 AttestationPermissionRequestSheetModel::GetStepDescription()
    const {
  return l10n_util::GetStringFUTF16(
      IDS_WEBAUTHN_REQUEST_ATTESTATION_PERMISSION_DESC,
      GetRelyingPartyIdString(dialog_model()));
}
