void StorageHandler::NotifyIndexedDBContentChanged(
    const std::string& origin,
    const base::string16& database_name,
    const base::string16& object_store_name) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);
  frontend_->IndexedDBContentUpdated(origin, base::UTF16ToUTF8(database_name),
                                     base::UTF16ToUTF8(object_store_name));
}
