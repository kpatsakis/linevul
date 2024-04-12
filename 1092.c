TouchEmulator* RenderWidgetHostImpl::GetTouchEmulator() {
  if (!delegate_ || !delegate_->GetInputEventRouter())
    return nullptr;

  return delegate_->GetInputEventRouter()->GetTouchEmulator();
}
