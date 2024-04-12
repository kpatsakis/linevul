std::string DoGetCurrentNetworkID(
    network::NetworkConnectionTracker* network_connection_tracker) {

  while (true) {
    auto connection_type = GetConnectionType(network_connection_tracker);
    std::string ssid_mccmnc;

    switch (connection_type) {
      case network::mojom::ConnectionType::CONNECTION_UNKNOWN:
      case network::mojom::ConnectionType::CONNECTION_NONE:
      case network::mojom::ConnectionType::CONNECTION_BLUETOOTH:
      case network::mojom::ConnectionType::CONNECTION_ETHERNET:
        break;
      case network::mojom::ConnectionType::CONNECTION_WIFI:
#if defined(OS_ANDROID)
        ssid_mccmnc = net::GetWifiSSID();
#endif
        break;
      case network::mojom::ConnectionType::CONNECTION_2G:
      case network::mojom::ConnectionType::CONNECTION_3G:
      case network::mojom::ConnectionType::CONNECTION_4G:
#if defined(OS_ANDROID)
        ssid_mccmnc = net::android::GetTelephonyNetworkOperator();
#endif
        break;
    }

    if (connection_type == GetConnectionType(network_connection_tracker)) {
      if (connection_type >= network::mojom::ConnectionType::CONNECTION_2G &&
          connection_type <= network::mojom::ConnectionType::CONNECTION_4G) {
        return "cell," + ssid_mccmnc;
      }
      return base::NumberToString(static_cast<int>(connection_type)) + "," +
             ssid_mccmnc;
    }
  }
  NOTREACHED();
}
