void ClassicPendingScript::FinishReadyStreaming() {
  CheckState();
  DCHECK(GetResource());
  DCHECK_EQ(ready_state_, kReadyStreaming);
  AdvanceReadyState(kReady);
}
