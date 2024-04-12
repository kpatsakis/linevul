void CloudPolicyController::DoWork() {
  switch (state_) {
    case STATE_TOKEN_UNAVAILABLE:
    case STATE_TOKEN_ERROR:
      FetchToken();
      return;
    case STATE_TOKEN_VALID:
    case STATE_POLICY_VALID:
    case STATE_POLICY_ERROR:
    case STATE_POLICY_UNAVAILABLE:
      SendPolicyRequest();
      return;
    case STATE_TOKEN_UNMANAGED:
      return;
  }

  NOTREACHED() << "Unhandled state" << state_;
}
