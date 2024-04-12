void RenderProcessHostImpl::ReceivedBadMessage() {
  if (run_renderer_in_process()) {
    CHECK(false);
  }
  NOTREACHED();
  base::KillProcess(GetHandle(), RESULT_CODE_KILLED_BAD_MESSAGE,
                    false);
}
