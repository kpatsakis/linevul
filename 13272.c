void TestRunner::Init(JobLevel job_level, TokenLevel startup_token,
                      TokenLevel main_token) {
  broker_ = NULL;
  policy_ = NULL;
  timeout_ = kDefaultTimeout;
  state_ = AFTER_REVERT;

  broker_ = GetBroker();
  if (!broker_)
    return;

  policy_ = broker_->CreatePolicy();
  if (!policy_)
    return;

  policy_->SetJobLevel(job_level, 0);
  policy_->SetTokenLevel(startup_token, main_token);

  is_init_ = true;
}
