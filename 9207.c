status_t BnOMXObserver::onTransact(
 uint32_t code, const Parcel &data, Parcel *reply, uint32_t flags) {
 switch (code) {
 case OBSERVER_ON_MSG:
 {
            CHECK_OMX_INTERFACE(IOMXObserver, data, reply);
            IOMX::node_id node = data.readInt32();
            std::list<omx_message> messages;
 status_t err = FAILED_TRANSACTION; // must receive at least one message
 do {
 int haveFence = data.readInt32();
 if (haveFence < 0) { // we use -1 to mark end of messages
 break;
 }
                omx_message msg;
                msg.node = node;
                msg.fenceFd = haveFence ? ::dup(data.readFileDescriptor()) : -1;
                msg.type = (typeof(msg.type))data.readInt32();
                err = data.read(&msg.u, sizeof(msg.u));
                ALOGV("onTransact reading message %d, size %zu", msg.type, sizeof(msg));
                messages.push_back(msg);
 } while (err == OK);

 if (err == OK) {
                onMessages(messages);
 }

 return err;
 }

 default:
 return BBinder::onTransact(code, data, reply, flags);
 }
}
