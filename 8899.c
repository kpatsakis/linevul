mojom::FrameInputHandler* TestRenderFrame::GetFrameInputHandler() {
  if (!frame_input_handler_) {
    mojom::FrameInputHandlerRequest frame_input_handler_request =
        mojo::MakeRequest(&frame_input_handler_);
    FrameInputHandlerImpl::CreateMojoService(
        weak_factory_.GetWeakPtr(), std::move(frame_input_handler_request));
  }
  return frame_input_handler_.get();
}
