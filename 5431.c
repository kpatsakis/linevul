void SoundTriggerHwService::Module::onCallbackEvent(const sp<CallbackEvent>& event)
{
    ALOGV("onCallbackEvent type %d", event->mType);

    sp<IMemory> eventMemory = event->mMemory;

 if (eventMemory == 0 || eventMemory->pointer() == NULL) {
 return;
 }
 if (mClient == 0) {
        ALOGI("%s mClient == 0", __func__);
 return;
 }

 switch (event->mType) {
 case CallbackEvent::TYPE_RECOGNITION: {
 struct sound_trigger_recognition_event *recognitionEvent =
 (struct sound_trigger_recognition_event *)eventMemory->pointer();
        sp<ISoundTriggerClient> client;
 {
 AutoMutex lock(mLock);
            sp<Model> model = getModel(recognitionEvent->model);
 if (model == 0) {
                ALOGW("%s model == 0", __func__);
 return;
 }
 if (model->mState != Model::STATE_ACTIVE) {
                ALOGV("onCallbackEvent model->mState %d != Model::STATE_ACTIVE", model->mState);
 return;
 }

            recognitionEvent->capture_session = model->mCaptureSession;
            model->mState = Model::STATE_IDLE;
            client = mClient;
 }
 if (client != 0) {
            client->onRecognitionEvent(eventMemory);
 }
 } break;
 case CallbackEvent::TYPE_SOUNDMODEL: {
 struct sound_trigger_model_event *soundmodelEvent =
 (struct sound_trigger_model_event *)eventMemory->pointer();
        sp<ISoundTriggerClient> client;
 {
 AutoMutex lock(mLock);
            sp<Model> model = getModel(soundmodelEvent->model);
 if (model == 0) {
                ALOGW("%s model == 0", __func__);
 return;
 }
            client = mClient;
 }
 if (client != 0) {
            client->onSoundModelEvent(eventMemory);
 }
 } break;
 case CallbackEvent::TYPE_SERVICE_STATE: {
        sp<ISoundTriggerClient> client;
 {
 AutoMutex lock(mLock);
            client = mClient;
 }
 if (client != 0) {
            client->onServiceStateChange(eventMemory);
 }
 } break;
 default:
        LOG_ALWAYS_FATAL("onCallbackEvent unknown event type %d", event->mType);
 }
}
