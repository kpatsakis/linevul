void RenderFrameImpl::BindMhtmlFileWriter(
    mojom::MhtmlFileWriterAssociatedRequest request) {
  mhtml_file_writer_binding_.Bind(
      std::move(request), GetTaskRunner(blink::TaskType::kInternalDefault));
}
