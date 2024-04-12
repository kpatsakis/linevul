void OfflinePageModelTaskified::GetPagesByNamespace(
    const std::string& name_space,
    const MultipleOfflinePageItemCallback& callback) {
  auto task = GetPagesTask::CreateTaskMatchingNamespace(store_.get(), callback,
                                                        name_space);
  task_queue_.AddTask(std::move(task));
}
