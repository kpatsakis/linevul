void SurfaceHitTestReadyNotifier::WaitForSurfaceReady(
    RenderWidgetHostViewBase* root_view) {
  viz::SurfaceId root_surface_id = root_view->GetCurrentSurfaceId();
  while (!ContainsSurfaceId(root_surface_id)) {
    base::RunLoop run_loop;
    base::ThreadTaskRunnerHandle::Get()->PostDelayedTask(
        FROM_HERE, run_loop.QuitClosure(), TestTimeouts::tiny_timeout());
    run_loop.Run();
  }
}
