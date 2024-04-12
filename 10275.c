void AutofillManager::SetExternalDelegate(AutofillExternalDelegate* delegate) {
  external_delegate_ = delegate;
  autocomplete_history_manager_->SetExternalDelegate(delegate);
}
