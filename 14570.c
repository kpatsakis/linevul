AccountInfo CreateTestAccountInfo(const std::string& name,
                                  bool is_hosted_domain,
                                  bool is_valid) {
  AccountInfo account_info;
  account_info.account_id = name;
  account_info.gaia = name;
  account_info.email = name + "@email.com";
  account_info.full_name = "name";
  account_info.given_name = "name";
  if (is_valid) {
    account_info.hosted_domain =
        is_hosted_domain ? "example.com"
                         : AccountTrackerService::kNoHostedDomainFound;
  }
  account_info.locale = "en";
  account_info.picture_url = "https://example.com";
  account_info.is_child_account = false;
  EXPECT_EQ(is_valid, account_info.IsValid());
  return account_info;
}
