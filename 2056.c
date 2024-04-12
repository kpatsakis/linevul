void ACodec::initiateConfigureComponent(const sp<AMessage> &msg) {
    msg->setWhat(kWhatConfigureComponent);
    msg->setTarget(this);
    msg->post();
}
