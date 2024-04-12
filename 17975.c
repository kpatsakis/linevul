void CastConfigDelegateChromeos::GetReceiversAndActivities(
    const ReceiversAndActivitesCallback& callback) {
  ExecuteJavaScriptWithCallback(
      "backgroundSetup.getMirrorCapableReceiversAndActivities();",
      base::Bind(&GetReceiversAndActivitiesCallback, callback));
}
