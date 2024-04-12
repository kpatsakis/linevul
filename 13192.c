void OMX::invalidateNodeID(node_id node) {
 Mutex::Autolock autoLock(mLock);
    invalidateNodeID_l(node);
}
