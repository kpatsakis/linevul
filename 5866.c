void DatabaseMessageFilter::OnDatabaseGetSpaceAvailable(
    const string16& origin_identifier, IPC::Message* reply_msg) {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::IO));
  DCHECK(db_tracker_->quota_manager_proxy());

  QuotaManager* quota_manager =
      db_tracker_->quota_manager_proxy()->quota_manager();
  if (!quota_manager) {
    NOTREACHED();  // The system is shutting down, messages are unexpected.
    DatabaseHostMsg_GetSpaceAvailable::WriteReplyParams(
        reply_msg, static_cast<int64>(0));
    Send(reply_msg);
    return;
  }

  quota_manager->GetUsageAndQuota(
      DatabaseUtil::GetOriginFromIdentifier(origin_identifier),
      quota::kStorageTypeTemporary,
      base::Bind(&DatabaseMessageFilter::OnDatabaseGetUsageAndQuota,
                 this, reply_msg));
}
