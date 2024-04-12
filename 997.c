void DebuggerGetTargetsFunction::SendTargetList(
    const std::vector<DevToolsTargetImpl*>& target_list) {
  scoped_ptr<base::ListValue> result(new base::ListValue());
  for (size_t i = 0; i < target_list.size(); ++i)
    result->Append(SerializeTarget(*target_list[i]));
  STLDeleteContainerPointers(target_list.begin(), target_list.end());
  SetResult(result.release());
  SendResponse(true);
}
