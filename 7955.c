void InputDispatcher::synthesizeCancelationEventsForAllConnectionsLocked(
 const CancelationOptions& options) {
 for (size_t i = 0; i < mConnectionsByFd.size(); i++) {
        synthesizeCancelationEventsForConnectionLocked(
                mConnectionsByFd.valueAt(i), options);
 }
}
