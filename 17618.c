static jboolean JNI_SendTabToSelfAndroidBridge_IsFeatureAvailable(
    JNIEnv* env,
    const JavaParamRef<jobject>& j_web_contents) {
  content::WebContents* web_contents =
      content::WebContents::FromJavaWebContents(j_web_contents);

   return ShouldOfferFeature(web_contents);
 }
