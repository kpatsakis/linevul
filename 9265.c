void DispatchCommand(Command* const command,
                     const std::string& method,
                     Response* response) {
  if (!command->Init(response))
    return;

  if (method == "POST") {
    command->ExecutePost(response);
  } else if (method == "GET") {
    command->ExecuteGet(response);
  } else if (method == "DELETE") {
    command->ExecuteDelete(response);
  } else {
    NOTREACHED();
  }
}
