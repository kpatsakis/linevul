void DocumentLoader::AppendRedirect(const KURL& url) {
  redirect_chain_.push_back(url);
}
