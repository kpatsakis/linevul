void InjectRawKeyEvent(WebContents* web_contents,
                       blink::WebInputEvent::Type type,
                       ui::DomKey key,
                       ui::DomCode code,
                       ui::KeyboardCode key_code,
                       int modifiers) {
  NativeWebKeyboardEvent event(type, modifiers, base::TimeTicks::Now());
  BuildSimpleWebKeyEvent(type, key, code, key_code, &event);
  WebContentsImpl* web_contents_impl =
      static_cast<WebContentsImpl*>(web_contents);
  RenderWidgetHostImpl* main_frame_rwh =
      web_contents_impl->GetMainFrame()->GetRenderWidgetHost();
  web_contents_impl->GetFocusedRenderWidgetHost(main_frame_rwh)
      ->ForwardKeyboardEvent(event);
}
