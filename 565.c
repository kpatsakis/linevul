void ComponentUpdaterPolicyTest::VerifyExpectations(bool update_disabled) {
  EXPECT_EQ(1, post_interceptor_->GetHitCount())
      << post_interceptor_->GetRequestsAsString();
  ASSERT_EQ(1, post_interceptor_->GetCount())
      << post_interceptor_->GetRequestsAsString();
  EXPECT_NE(std::string::npos,
            post_interceptor_->GetRequestBody(0).find(base::StringPrintf(
                "<updatecheck%s/>",
                update_disabled ? " updatedisabled=\"true\"" : "")));
}
