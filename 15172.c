void DataReductionProxyIOData::SetInt64Pref(const std::string& pref_path,
                                            int64_t value) {
  DCHECK(io_task_runner_->BelongsToCurrentThread());
  ui_task_runner_->PostTask(
      FROM_HERE, base::BindOnce(&DataReductionProxyService::SetInt64Pref,
                                service_, pref_path, value));
}
