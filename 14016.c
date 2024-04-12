void RenderWidgetHostImpl::Init() {
  DCHECK(process_->HasConnection());

  renderer_initialized_ = true;

  if (view_) {
    Send(new ViewMsg_SetSurfaceIdNamespace(routing_id_,
                                           view_->GetSurfaceIdNamespace()));
  }

  SendScreenRects();
  WasResized();

  if (owner_delegate_)
    owner_delegate_->RenderWidgetDidInit();
}
