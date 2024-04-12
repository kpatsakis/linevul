void PPAPITestBase::RunTestAndReload(const std::string& test_case) {
  GURL url = GetTestFileUrl(test_case);
  RunTestURL(url);
  RunTestURL(url);
}
