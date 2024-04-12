void RenderFrameDevToolsAgentHost::InspectElement(
    DevToolsSession* session,
    int x,
    int y) {

  if (frame_tree_node_) {
    if (auto* main_view =
            frame_tree_node_->frame_tree()->GetMainFrame()->GetView()) {
      gfx::Point transformed_point = gfx::ToRoundedPoint(
          main_view->TransformRootPointToViewCoordSpace(gfx::PointF(x, y)));
      x = transformed_point.x();
      y = transformed_point.y();
    }
  }

  session->InspectElement(gfx::Point(x, y));
}
