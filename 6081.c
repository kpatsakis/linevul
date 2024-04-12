wifi_error wifi_set_scanning_mac_oui(wifi_interface_handle handle, oui scan_oui)
{
 SetPnoMacAddrOuiCommand command(handle, scan_oui);
 return (wifi_error)command.start();

}
