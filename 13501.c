SendTabToSelfModel* GetModel(const JavaParamRef<jobject>& j_profile) {
  Profile* profile = ProfileAndroid::FromProfileAndroid(j_profile);
  SendTabToSelfModel* model = SendTabToSelfSyncServiceFactory::GetInstance()
                                  ->GetForProfile(profile)
                                  ->GetSendTabToSelfModel();
  LogModelLoadedInTime(model->IsReady());
  return model;
}
