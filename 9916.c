void SoundTriggerHwService::sendSoundModelEvent(struct sound_trigger_model_event *event,
 Module *module)
{
 AutoMutex lock(mServiceLock);
    sp<IMemory> eventMemory = prepareSoundModelEvent_l(event);
 if (eventMemory == 0) {
 return;
 }
    sp<Module> strongModule;
 for (size_t i = 0; i < mModules.size(); i++) {
 if (mModules.valueAt(i).get() == module) {
            strongModule = mModules.valueAt(i);
 break;
 }
 }
 if (strongModule == 0) {
 return;
 }
    sendCallbackEvent_l(new CallbackEvent(CallbackEvent::TYPE_SOUNDMODEL,
                                                 eventMemory, strongModule));
}
