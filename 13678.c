void RenderFrameImpl::WillInsertBody() {
  Send(new FrameHostMsg_WillInsertBody(routing_id_,
                                       render_view_->GetRoutingID()));
}
