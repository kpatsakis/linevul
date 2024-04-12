void DocumentLoader::WillCommitNavigation() {
  if (GetFrameLoader().StateMachine()->CreatingInitialEmptyDocument())
    return;
  probe::willCommitLoad(frame_, this);
  frame_->GetIdlenessDetector()->WillCommitLoad();
}
