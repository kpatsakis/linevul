void WebContentsAndroid::AddStyleSheetByURL(
    JNIEnv* env,
    jobject obj,
    jstring url) {
  web_contents_->GetMainFrame()->Send(new FrameMsg_AddStyleSheetByURL(
      web_contents_->GetMainFrame()->GetRoutingID(),
      ConvertJavaStringToUTF8(env, url)));
}
