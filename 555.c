bool ShouldShowNetworkIconInTray(const Network* network) {
  if (!network)
    return true;
  return !network->connected() || network->type() != TYPE_ETHERNET;
}
