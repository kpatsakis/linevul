void BrowserPluginGuest::Resize(
    RenderViewHost* embedder_rvh,
    const BrowserPluginHostMsg_ResizeGuest_Params& params) {
  RenderWidgetHostImpl* render_widget_host =
      RenderWidgetHostImpl::From(web_contents()->GetRenderViewHost());
  render_widget_host->ResetSizeAndRepaintPendingFlags();
  if (!TransportDIB::is_valid_id(params.damage_buffer_id)) {
    if (!params.view_size.IsEmpty())
      web_contents()->GetView()->SizeContents(params.view_size);
    return;
  }
  TransportDIB* damage_buffer =
      GetDamageBufferFromEmbedder(embedder_rvh, params);
  SetDamageBuffer(damage_buffer,
#if defined(OS_WIN)
                  params.damage_buffer_size,
                  params.damage_buffer_id.handle,
#endif
                  params.view_size,
                  params.scale_factor);
  web_contents()->GetView()->SizeContents(params.view_size);
}
