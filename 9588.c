static void CreateContextProviderOnMainThread(
    ContextProviderCreationInfo* creation_info,
    WaitableEvent* waitable_event) {
  DCHECK(IsMainThread());
  *creation_info->using_gpu_compositing =
      !Platform::Current()->IsGpuCompositingDisabled();
  creation_info->created_context_provider =
      Platform::Current()->CreateOffscreenGraphicsContext3DProvider(
          creation_info->context_attributes, creation_info->url, nullptr,
          creation_info->gl_info);
  waitable_event->Signal();
}
