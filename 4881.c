InputDispatcher::EventEntry::~EventEntry() {
    releaseInjectionState();
}
