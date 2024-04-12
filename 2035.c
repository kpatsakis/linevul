PasswordStoreLoginsChangedObserver::PasswordStoreLoginsChangedObserver(
    AutomationProvider* automation,
    IPC::Message* reply_message,
    PasswordStoreChange::Type expected_type,
    const std::string& result_key)
    : automation_(automation->AsWeakPtr()),
      reply_message_(reply_message),
      expected_type_(expected_type),
      result_key_(result_key),
      done_event_(false, false) {
  AddRef();
}
