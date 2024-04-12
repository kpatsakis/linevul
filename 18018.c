void BluetoothOptionsHandler::Initialize() {
  DCHECK(web_ui_);
  if (!CommandLine::ForCurrentProcess()
      ->HasSwitch(switches::kEnableBluetooth)) {
    return;
  }

  web_ui_->CallJavascriptFunction(
      "options.SystemOptions.showBluetoothSettings");

  bool bluetooth_on = true;
  base::FundamentalValue checked(bluetooth_on);
  web_ui_->CallJavascriptFunction(
      "options.SystemOptions.setBluetoothCheckboxState", checked);

  chromeos::BluetoothManager* bluetooth_manager =
      chromeos::BluetoothManager::GetInstance();
  DCHECK(bluetooth_manager);
  bluetooth_manager->AddObserver(this);

  chromeos::BluetoothAdapter* default_adapter =
      bluetooth_manager->DefaultAdapter();
  DefaultAdapterChanged(default_adapter);
}
