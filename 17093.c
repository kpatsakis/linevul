void Document::DecrementPasswordCount() {
  DCHECK_GT(password_count_, 0u);
  --password_count_;
  if (IsSecureContext() || password_count_ > 0)
    return;
  SendSensitiveInputVisibility();
}
