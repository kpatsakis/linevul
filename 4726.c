void ClearShaderCacheOnIOThread(const base::FilePath& path,
                                const base::Time begin,
                                const base::Time end,
                                base::OnceClosure callback) {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);
  GetShaderCacheFactorySingleton()->ClearByPath(
      path, begin, end,
      base::BindOnce(&ClearedShaderCache, std::move(callback)));
}
