void RenderFrameImpl::BindFrameBindingsControl(
    mojom::FrameBindingsControlAssociatedRequest request) {
  frame_bindings_control_binding_.Bind(
      std::move(request), GetTaskRunner(blink::TaskType::kInternalIPC));
}
