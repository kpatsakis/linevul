void OfflinePageModelImpl::GetPagesSupportedByDownloads(
    const MultipleOfflinePageItemCallback& callback) {
  OfflinePageModelQueryBuilder builder;
  builder.RequireSupportedByDownload(
      OfflinePageModelQuery::Requirement::INCLUDE_MATCHING);
  RunWhenLoaded(
      base::Bind(&OfflinePageModelImpl::GetPagesMatchingQueryWhenLoadDone,
                 weak_ptr_factory_.GetWeakPtr(),
                 base::Passed(builder.Build(GetPolicyController())), callback));
}
