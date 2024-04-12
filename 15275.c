  explicit FrameURLLoaderFactory(base::WeakPtr<RenderFrameImpl> frame)
      : frame_(std::move(frame)) {}
