void AuthenticatorBlePowerOnAutomaticSheetModel::OnAccept() {
  busy_powering_on_ble_ = true;
  dialog_model()->OnSheetModelDidChange();
  dialog_model()->PowerOnBleAdapter();
}
