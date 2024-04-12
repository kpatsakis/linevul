Response PageHandler::Enable() {
  enabled_ = true;
  if (GetWebContents() && GetWebContents()->ShowingInterstitialPage())
    frontend_->InterstitialShown();
  return Response::FallThrough();
}
