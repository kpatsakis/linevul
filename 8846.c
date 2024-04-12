viz::SurfaceId DelegatedFrameHost::SurfaceIdAtPoint(
    viz::SurfaceHittestDelegate* delegate,
    const gfx::Point& point,
    gfx::Point* transformed_point) {
  viz::SurfaceId surface_id(frame_sink_id_, local_surface_id_);
  if (!surface_id.is_valid())
    return surface_id;
  viz::SurfaceHittest hittest(delegate,
                              GetFrameSinkManager()->surface_manager());
  gfx::Transform target_transform;
  viz::SurfaceId target_local_surface_id =
      hittest.GetTargetSurfaceAtPoint(surface_id, point, &target_transform);
  *transformed_point = point;
  if (target_local_surface_id.is_valid())
    target_transform.TransformPoint(transformed_point);
  return target_local_surface_id;
}
