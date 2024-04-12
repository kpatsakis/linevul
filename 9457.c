void NotifyFinishObservers(
    HeapHashSet<WeakMember<ResourceFinishObserver>>* observers) {
  for (const auto& observer : *observers)
    observer->NotifyFinished();
}
