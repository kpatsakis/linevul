RefPtr<SecurityOrigin> FrameFetchContext::GetRequestorOriginForFrameLoading() {
  if (IsDetached())
    return frozen_state_->requestor_origin;

  return GetFrame()->GetDocument()->GetSecurityOrigin();
}
