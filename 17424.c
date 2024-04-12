ULONG DataObjectImpl::Release() {
  base::RefCountedThreadSafe<DownloadFileObserver>::Release();
  return 0;
}
