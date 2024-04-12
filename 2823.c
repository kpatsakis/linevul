void InputDispatcher::traceInboundQueueLengthLocked() {
 if (ATRACE_ENABLED()) {
        ATRACE_INT("iq", mInboundQueue.count());
 }
}
