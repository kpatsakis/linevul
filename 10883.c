  void FileSelectionCanceled() {
    proxy_ = nullptr;
    if (!render_frame_host_)
      return;
    std::move(callback_).Run(nullptr);
  }
