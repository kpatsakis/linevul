void TestingAutomationProvider::GetInitialLoadTimes(
    Browser*,
    DictionaryValue*,
    IPC::Message* reply_message) {
  scoped_ptr<DictionaryValue> return_value(
      initial_load_observer_->GetTimingInformation());

  std::string json_return;
  base::JSONWriter::Write(return_value.get(), false, &json_return);
  AutomationMsg_SendJSONRequest::WriteReplyParams(
      reply_message, json_return, true);
  Send(reply_message);
}
