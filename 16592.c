QuotaManager::QuotaManager(bool is_incognito,
                           const FilePath& profile_path,
                           base::SingleThreadTaskRunner* io_thread,
                           base::SequencedTaskRunner* db_thread,
                           SpecialStoragePolicy* special_storage_policy)
  : is_incognito_(is_incognito),
    profile_path_(profile_path),
    proxy_(new QuotaManagerProxy(
        ALLOW_THIS_IN_INITIALIZER_LIST(this), io_thread)),
    db_disabled_(false),
    eviction_disabled_(false),
    io_thread_(io_thread),
    db_thread_(db_thread),
    temporary_quota_initialized_(false),
    temporary_quota_override_(-1),
    desired_available_space_(-1),
    special_storage_policy_(special_storage_policy),
    weak_factory_(ALLOW_THIS_IN_INITIALIZER_LIST(this)),
    get_disk_space_fn_(&base::SysInfo::AmountOfFreeDiskSpace) {
}
