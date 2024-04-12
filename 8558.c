void RenderViewTest::GoToOffset(int offset, const PageState& state) {
  RenderViewImpl* impl = static_cast<RenderViewImpl*>(view_);

  int history_list_length = impl->historyBackListCount() +
                            impl->historyForwardListCount() + 1;
  int pending_offset = offset + impl->history_list_offset_;

  CommonNavigationParams common_params(
      GURL(), Referrer(), ui::PAGE_TRANSITION_FORWARD_BACK,
      FrameMsg_Navigate_Type::NORMAL, true, false, base::TimeTicks(),
      FrameMsg_UILoadMetricsReportType::NO_REPORT, GURL(), GURL());
  RequestNavigationParams request_params;
  request_params.page_state = state;
  request_params.page_id = impl->page_id_ + offset;
  request_params.nav_entry_id = pending_offset + 1;
  request_params.pending_history_list_offset = pending_offset;
  request_params.current_history_list_offset = impl->history_list_offset_;
  request_params.current_history_list_length = history_list_length;

  TestRenderFrame* frame =
      static_cast<TestRenderFrame*>(impl->GetMainRenderFrame());
  frame->Navigate(common_params, StartNavigationParams(), request_params);

  FrameLoadWaiter(frame).Wait();
}
