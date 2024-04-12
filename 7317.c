void WebKitTestController::OnGpuProcessCrashed(
    base::TerminationStatus exit_code) {
  DCHECK(CalledOnValidThread());
  printer_->AddErrorMessage("#CRASHED - gpu");
  DiscardMainWindow();
}
