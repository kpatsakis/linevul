void RenderProcessHostImpl::BindSharedBitmapAllocationNotifier(
    viz::mojom::SharedBitmapAllocationNotifierRequest request) {
  shared_bitmap_allocation_notifier_impl_.Bind(std::move(request));
}
