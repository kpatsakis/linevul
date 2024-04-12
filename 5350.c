static jlong Init(JNIEnv* env,
                  const JavaParamRef<jclass>&,
                  const JavaParamRef<jobject>& browser_context) {
  scoped_ptr<WebContents> web_contents(content::WebContents::Create(
      content::WebContents::CreateParams(AwBrowserContext::GetDefault())));
  return reinterpret_cast<intptr_t>(new AwContents(web_contents.Pass()));
}
