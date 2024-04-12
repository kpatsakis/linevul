void Job::DispatchAlertOrErrorOnOriginThread(bool is_alert,
                                             int line_number,
                                             const base::string16& message) {
  CheckIsOnOriginThread();

  if (cancelled_.IsSet())
    return;

  if (is_alert) {
    VLOG(1) << "PAC-alert: " << message;

    bindings_->Alert(message);
  } else {
    if (line_number == -1)
      VLOG(1) << "PAC-error: " << message;
    else
      VLOG(1) << "PAC-error: " << "line: " << line_number << ": " << message;

    bindings_->OnError(line_number, message);
  }
}
