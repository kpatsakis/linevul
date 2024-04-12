DataUseUserData::AppState GetCurrentAppState() {
#if defined(OS_ANDROID)
  return base::android::ApplicationStatusListener::GetState() ==
                 base::android::APPLICATION_STATE_HAS_RUNNING_ACTIVITIES
             ? DataUseUserData::FOREGROUND
             : DataUseUserData::BACKGROUND;
#else
  return DataUseUserData::FOREGROUND;
#endif
}
