void SoundTriggerHwService::CallbackThread::onFirstRef()
{
    run("soundTrigger cbk", ANDROID_PRIORITY_URGENT_AUDIO);
}
