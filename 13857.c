void ClearedShaderCache(base::OnceClosure callback) {
  if (!BrowserThread::CurrentlyOn(BrowserThread::UI)) {
    base::PostTaskWithTraits(
        FROM_HERE, {BrowserThread::UI},
        base::BindOnce(&ClearedShaderCache, std::move(callback)));
    return;
  }
  std::move(callback).Run();
}
