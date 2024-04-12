void WebContentsAndroid::ShowImeIfNeeded(JNIEnv* env, jobject obj) {
  RenderViewHost* host = web_contents_->GetRenderViewHost();
  if (!host)
    return;
  host->Send(new ViewMsg_ShowImeIfNeeded(host->GetRoutingID()));
}
