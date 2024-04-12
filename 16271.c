bool SetTemporaryGlobalOverrideQuotaOnDBThread(int64* new_quota,
                                               QuotaDatabase* database) {
  DCHECK(database);
  if (!database->SetQuotaConfigValue(
          QuotaDatabase::kTemporaryQuotaOverrideKey, *new_quota)) {
    *new_quota = -1;
    return false;
  }
  return true;
}
