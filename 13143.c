sp<SoundTriggerHwService::Model> SoundTriggerHwService::Module::getModel(
 sound_model_handle_t handle)
{
    sp<Model> model;
 ssize_t index = mModels.indexOfKey(handle);
 if (index >= 0) {
        model = mModels.valueAt(index);
 }
 return model;
}
