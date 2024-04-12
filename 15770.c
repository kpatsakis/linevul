SynchronizeVisualPropertiesMessageFilter::WaitForSurfaceId() {
  surface_id_run_loop_.reset(new base::RunLoop);
  surface_id_run_loop_->Run();
  return last_surface_id_;
}
