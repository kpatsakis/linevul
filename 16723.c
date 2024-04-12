void ChromeClientImpl::AttachRootGraphicsLayer(GraphicsLayer* root_layer,
                                               LocalFrame* local_frame) {
  DCHECK(!RuntimeEnabledFeatures::SlimmingPaintV2Enabled());
  WebLocalFrameImpl* web_frame =
      WebLocalFrameImpl::FromFrame(local_frame)->LocalRoot();

  DCHECK(web_frame->FrameWidget() || !root_layer);
  if (web_frame->FrameWidget())
    web_frame->FrameWidget()->SetRootGraphicsLayer(root_layer);
}
