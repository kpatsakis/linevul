void InterstitialPageImpl::OnNavigatingAwayOrTabClosing() {
  if (action_taken_ == NO_ACTION) {
    DontProceed();
  } else {
    Hide();
  }
}
