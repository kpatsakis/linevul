void WebContentsAndroid::HideTransitionElements(JNIEnv* env,
                                                jobject jobj,
                                                jstring css_selector) {
  web_contents_->GetMainFrame()->Send(
      new FrameMsg_HideTransitionElements(
          web_contents_->GetMainFrame()->GetRoutingID(),
          ConvertJavaStringToUTF8(env, css_selector)));
}
