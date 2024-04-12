void NetworkChangeNotifier::NotifyObserversOfDNSChange() {
  if (g_network_change_notifier) {
    g_network_change_notifier->resolver_state_observer_list_->Notify(
        &DNSObserver::OnDNSChanged);
  }
}
