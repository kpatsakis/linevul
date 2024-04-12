void NotifyRenderFrameDetachedOnIO(int render_process_id, int render_frame_id) {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);
  SharedWorkerServiceImpl::GetInstance()->RenderFrameDetached(render_process_id,
                                                              render_frame_id);
}
