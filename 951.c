void OfflinePageModelTaskified::InformDeletePageDone(
    const DeletePageCallback& callback,
    DeletePageResult result) {
  if (!callback.is_null())
    callback.Run(result);
}
