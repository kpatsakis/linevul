static void LaunchDownloadOverwriteInfoBar(
    JNIEnv* env,
    const JavaParamRef<jclass>& clazz,
    const JavaParamRef<jobject>& delegate,
    const JavaParamRef<jobject>& tab,
    const JavaParamRef<jobject>& download_info,
    const JavaParamRef<jstring>& jfile_name,
    const JavaParamRef<jstring>& jdir_name,
    const JavaParamRef<jstring>& jdir_full_path) {
  TabAndroid* tab_android = TabAndroid::GetNativeTab(env, tab);

  std::string file_name =
      base::android::ConvertJavaStringToUTF8(env, jfile_name);
  std::string dir_name = base::android::ConvertJavaStringToUTF8(env, jdir_name);
  std::string dir_full_path =
      base::android::ConvertJavaStringToUTF8(env, jdir_full_path);

  chrome::android::AndroidDownloadManagerOverwriteInfoBarDelegate::Create(
      InfoBarService::FromWebContents(tab_android->web_contents()), file_name,
      dir_name, dir_full_path, delegate, download_info);
}
