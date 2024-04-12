void DebuggerGetTargetsFunction::SendTargetList(
    const content::DevToolsAgentHost::List& target_list) {
  std::unique_ptr<base::ListValue> result(new base::ListValue());
  for (size_t i = 0; i < target_list.size(); ++i)
    result->Append(SerializeTarget(target_list[i]));
  SetResult(std::move(result));
  SendResponse(true);
}
