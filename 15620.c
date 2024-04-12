void BackgroundLoaderOffliner::SetBackgroundSnapshotControllerForTest(
    std::unique_ptr<BackgroundSnapshotController> controller) {
  snapshot_controller_ = std::move(controller);
}
