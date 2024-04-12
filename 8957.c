void JNI_OfflinePageDownloadBridge_StartDownload(
    JNIEnv* env,
    const JavaParamRef<jclass>& clazz,
    const JavaParamRef<jobject>& j_tab,
    const JavaParamRef<jstring>& j_origin) {
  TabAndroid* tab = TabAndroid::GetNativeTab(env, j_tab);
  if (!tab)
    return;

  content::WebContents* web_contents = tab->web_contents();
  if (!web_contents)
    return;

  std::string origin = ConvertJavaStringToUTF8(env, j_origin);
  ScopedJavaGlobalRef<jobject> j_tab_ref(env, j_tab);

  content::ResourceRequestInfo::WebContentsGetter web_contents_getter =
      GetWebContentsGetter(web_contents);
  DownloadControllerBase::Get()->AcquireFileAccessPermission(
      web_contents_getter,
      base::Bind(&OnOfflinePageAcquireFileAccessPermissionDone,
                 web_contents_getter, j_tab_ref, origin));
}
