void WebXrControllerInputMock::OnFrameSubmitted(
    device_test::mojom::SubmittedFrameDataPtr frame_data,
    device_test::mojom::XRTestHook::OnFrameSubmittedCallback callback) {
  num_submitted_frames_++;
  if (wait_loop_ && target_submitted_frames_ == num_submitted_frames_) {
    wait_loop_->Quit();
  }
  std::move(callback).Run();
}
