void OMX::CallbackDispatcher::dispatch(std::list<omx_message> &messages) {
 if (mOwner == NULL) {
        ALOGV("Would have dispatched a message to a node that's already gone.");
 return;
 }
    mOwner->onMessages(messages);
}
