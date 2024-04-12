void NetworkChangeNotifier::AddDNSObserver(DNSObserver* observer) {
  if (g_network_change_notifier) {
    g_network_change_notifier->resolver_state_observer_list_->AddObserver(
        observer);
  }
}
