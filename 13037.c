void ChromeContentUtilityClient::SetNetworkBinderCreationCallback(
    const NetworkBinderCreationCallback& callback) {
  g_network_binder_creation_callback.Get() = callback;
}
