void ResourceDispatcherHost::RemoveObserver(Observer* obs) {
  observer_list_.RemoveObserver(obs);
}
