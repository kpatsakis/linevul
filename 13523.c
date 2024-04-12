void LocalFrame::SetAdTrackerForTesting(AdTracker* ad_tracker) {
  ad_tracker_->Shutdown();
  ad_tracker_ = ad_tracker;
}
