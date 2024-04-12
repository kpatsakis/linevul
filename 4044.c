void DelegatedFrameHost::BeginFrameSubscription(
    std::unique_ptr<RenderWidgetHostViewFrameSubscriber> subscriber) {
  frame_subscriber_ = std::move(subscriber);
}
