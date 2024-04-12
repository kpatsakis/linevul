bool HeadlessDevToolsManagerDelegate::HandleAsyncCommand(
    content::DevToolsAgentHost* agent_host,
    int session_id,
    base::DictionaryValue* command,
    const CommandCallback& callback) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);

  if (!browser_)
    return false;

  const base::Value* id_value = command->FindKey("id");
  const base::Value* method_value = command->FindKey("method");
  if (!id_value || !method_value)
    return false;

  auto find_it = async_command_map_.find(method_value->GetString());
  if (find_it == async_command_map_.end())
    return false;

  const base::DictionaryValue* params = nullptr;
  command->GetDictionary("params", &params);
  find_it->second.Run(agent_host, session_id, id_value->GetInt(), params,
                      callback);
  return true;
}
