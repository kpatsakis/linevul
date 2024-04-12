void RenderWidgetHostImpl::CompositorFrameDrawn(
    const std::vector<ui::LatencyInfo>& latency_info) {
  for (size_t i = 0; i < latency_info.size(); i++) {
    std::set<RenderWidgetHostImpl*> rwhi_set;
    for (const auto& lc : latency_info[i].latency_components()) {
      if (lc.first.first == ui::INPUT_EVENT_LATENCY_BEGIN_RWH_COMPONENT ||
          lc.first.first == ui::WINDOW_SNAPSHOT_FRAME_NUMBER_COMPONENT ||
          lc.first.first == ui::TAB_SHOW_COMPONENT) {
        int routing_id = lc.first.second & 0xffffffff;
        int process_id = (lc.first.second >> 32) & 0xffffffff;
        RenderWidgetHost* rwh =
            RenderWidgetHost::FromID(process_id, routing_id);
        if (!rwh) {
          continue;
        }
        RenderWidgetHostImpl* rwhi = RenderWidgetHostImpl::From(rwh);
        if (rwhi_set.insert(rwhi).second)
          rwhi->FrameSwapped(latency_info[i]);
      }
    }
  }
}
