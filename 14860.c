void RenderWidgetHostImpl::Copy() {
  Send(new ViewMsg_Copy(GetRoutingID()));
  RecordAction(UserMetricsAction("Copy"));
}
