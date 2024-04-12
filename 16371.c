void SearchProviderTest::SetUp() {
  SearchProvider::set_query_suggest_immediately(true);

  profile_.CreateHistoryService(true, false);
  profile_.CreateTemplateURLModel();

  TemplateURLModel* turl_model = profile_.GetTemplateURLModel();

  default_t_url_ = new TemplateURL();
  default_t_url_->SetURL("http://defaultturl/{searchTerms}", 0, 0);
  default_t_url_->SetSuggestionsURL("http://defaultturl2/{searchTerms}", 0, 0);
  turl_model->Add(default_t_url_);
  turl_model->SetDefaultSearchProvider(default_t_url_);
  TemplateURL::IDType default_provider_id = default_t_url_->id();
  ASSERT_NE(0, default_provider_id);

  HistoryService* history =
      profile_.GetHistoryService(Profile::EXPLICIT_ACCESS);
  term1_url_ = GURL(default_t_url_->url()->ReplaceSearchTerms(
      *default_t_url_, UTF16ToWide(term1_), 0, std::wstring()));
  history->AddPageWithDetails(term1_url_, string16(), 1, 1,
                              base::Time::Now(), false);
  history->SetKeywordSearchTermsForURL(term1_url_, default_t_url_->id(),
                                       term1_);

  keyword_t_url_ = new TemplateURL();
  keyword_t_url_->set_keyword(L"k");
  keyword_t_url_->SetURL("http://keyword/{searchTerms}", 0, 0);
  keyword_t_url_->SetSuggestionsURL("http://suggest_keyword/{searchTerms}", 0,
                                    0);
  profile_.GetTemplateURLModel()->Add(keyword_t_url_);
  ASSERT_NE(0, keyword_t_url_->id());

  keyword_url_ = GURL(keyword_t_url_->url()->ReplaceSearchTerms(
      *keyword_t_url_, UTF16ToWide(keyword_term_), 0, std::wstring()));
  history->AddPageWithDetails(keyword_url_, string16(), 1, 1,
                              base::Time::Now(), false);
  history->SetKeywordSearchTermsForURL(keyword_url_, keyword_t_url_->id(),
                                       keyword_term_);

  provider_ = new SearchProvider(this, &profile_);

  URLFetcher::set_factory(&test_factory_);
}
