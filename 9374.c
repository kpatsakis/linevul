void SynchronousCompositorOutputSurface::SetSyncClient(
    SynchronousCompositorOutputSurfaceClient* compositor) {
  DCHECK(CalledOnValidThread());
  sync_client_ = compositor;
}
