  void OnSecondResult(std::unique_ptr<runtime::EvaluateResult> result) {
    EXPECT_TRUE(result->GetResult()->HasValue());
    EXPECT_EQ(27 * 4, result->GetResult()->GetValue()->GetInt());

    FinishAsynchronousTest();
  }
