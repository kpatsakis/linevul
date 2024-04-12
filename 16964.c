void ComponentUpdaterPolicyTest::FinishDefaultPolicy_GroupPolicyNotSupported() {
  VerifyExpectations(!kUpdateDisabled);

  cur_test_case_ = std::make_pair(
      &ComponentUpdaterPolicyTest::EnabledPolicy_GroupPolicySupported,
      &ComponentUpdaterPolicyTest::FinishEnabledPolicy_GroupPolicySupported);
  CallAsync(cur_test_case_.first);
}
