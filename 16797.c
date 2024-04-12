void OfflinePageModelImpl::GetPagesByURL(
    const GURL& url,
    URLSearchMode url_search_mode,
    const MultipleOfflinePageItemCallback& callback) {
  OfflinePageModelQueryBuilder builder;
  builder.SetUrls(OfflinePageModelQuery::Requirement::INCLUDE_MATCHING,
                  std::vector<GURL>({url}), url_search_mode,
                  true /* strip_fragment */);
  RunWhenLoaded(
      base::Bind(&OfflinePageModelImpl::GetPagesMatchingQueryWhenLoadDone,
                 weak_ptr_factory_.GetWeakPtr(),
                 base::Passed(builder.Build(GetPolicyController())), callback));
}
