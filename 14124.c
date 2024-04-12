void DatabaseImpl::RemoveObservers(const std::vector<int32_t>& observers) {
  idb_runner_->PostTask(FROM_HERE,
                        base::Bind(&IDBThreadHelper::RemoveObservers,
                                   base::Unretained(helper_), observers));
}
