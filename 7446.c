void GpuVideoDecodeAccelerator::NotifyResetDone() {
  if (!Send(new AcceleratedVideoDecoderHostMsg_ResetDone(host_route_id_)))
    DLOG(ERROR) << "Send(AcceleratedVideoDecoderHostMsg_ResetDone) failed";
}
