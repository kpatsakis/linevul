bool ACodec::OutputPortSettingsChangedState::onMessageReceived(
 const sp<AMessage> &msg) {
 bool handled = false;

 switch (msg->what()) {
 case kWhatFlush:
 case kWhatShutdown:
 case kWhatResume:
 case kWhatSetParameters:
 {
 if (msg->what() == kWhatResume) {
                ALOGV("[%s] Deferring resume", mCodec->mComponentName.c_str());
 }

            mCodec->deferMessage(msg);
            handled = true;
 break;
 }

 default:
            handled = BaseState::onMessageReceived(msg);
 break;
 }

 return handled;
}
