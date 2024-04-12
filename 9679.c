blink::WebString RenderViewImpl::AcceptLanguages() {
  return WebString::FromUTF8(renderer_preferences_.accept_languages);
}
