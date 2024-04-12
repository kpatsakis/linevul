  void CheckMaybeActivateDataReductionProxy(bool initially_enabled,
                                            bool request_succeeded,
                                            bool expected_enabled,
                                            bool expected_restricted,
                                            bool expected_fallback_restricted) {
    test_context_->SetDataReductionProxyEnabled(initially_enabled);
    test_context_->config()->UpdateConfigForTesting(initially_enabled,
                                                    request_succeeded, true);
    ExpectSetProxyPrefs(expected_enabled, false);
     settings_->MaybeActivateDataReductionProxy(false);
     test_context_->RunUntilIdle();
   }
