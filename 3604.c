void SynchronousCompositorImpl::SetClient(
    SynchronousCompositorClient* compositor_client) {
  DCHECK(CalledOnValidThread());
  DCHECK_IMPLIES(compositor_client, !compositor_client_);
  DCHECK_IMPLIES(!compositor_client, compositor_client_);

  if (!compositor_client) {
    SynchronousCompositorRegistry::GetInstance()->UnregisterCompositor(
        routing_id_, this);
  }

  compositor_client_ = compositor_client;

  if (compositor_client_) {
    SynchronousCompositorRegistry::GetInstance()->RegisterCompositor(
        routing_id_, this);
   }
 }
