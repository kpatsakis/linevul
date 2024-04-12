void OfflinePageModelTaskified::RemovePagesMatchingUrlAndNamespace(
    const OfflinePageItem& page) {
  auto task = DeletePageTask::CreateTaskDeletingForPageLimit(
      store_.get(),
      base::BindOnce(&OfflinePageModelTaskified::OnDeleteDone,
                     weak_ptr_factory_.GetWeakPtr(),
                     base::Bind([](DeletePageResult result) {})),
      policy_controller_.get(), page);
  task_queue_.AddTask(std::move(task));
}
