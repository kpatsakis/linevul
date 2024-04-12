void TaskManagerHandler::HandleActivatePage(const ListValue* unique_ids) {
  for (ListValue::const_iterator i = unique_ids->begin();
       i != unique_ids->end(); ++i) {
    int unique_id = parseIndex(*i);
    int resource_index = model_->GetResourceIndexByUniqueId(unique_id);
    if (resource_index == -1)
      continue;

    task_manager_->ActivateProcess(resource_index);
    break;
  }
}
