void DevToolsHttpHandler::SendJson(int connection_id,
                                   net::HttpStatusCode status_code,
                                   base::Value* value,
                                   const std::string& message) {
  if (!thread_)
    return;

  std::string json_value;
  if (value) {
    base::JSONWriter::WriteWithOptions(
        *value, base::JSONWriter::OPTIONS_PRETTY_PRINT, &json_value);
  }
  std::string json_message;
  base::JSONWriter::Write(base::Value(message), &json_message);

  net::HttpServerResponseInfo response(status_code);
  response.SetBody(json_value + message, "application/json; charset=UTF-8");

  thread_->task_runner()->PostTask(
      FROM_HERE, base::BindOnce(&ServerWrapper::SendResponse,
                                base::Unretained(server_wrapper_.get()),
                                connection_id, response));
}
