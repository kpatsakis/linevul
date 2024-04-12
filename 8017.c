bool LocalFrame::IsProvisional() const {
  CHECK_NE(FrameLifecycle::kDetached, lifecycle_.GetState());

  if (IsMainFrame()) {
    return GetPage()->MainFrame() != this;
  }

  DCHECK(Owner());
  return Owner()->ContentFrame() != this;
}
