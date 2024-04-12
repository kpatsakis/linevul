void RenderWidgetHostImpl::UpdateVSyncParameters(base::TimeTicks timebase,
                                                 base::TimeDelta interval) {
  Send(new ViewMsg_UpdateVSyncParameters(GetRoutingID(), timebase, interval));
}
