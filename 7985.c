void AutofillMetricsTest::PurgeUKM() {
  autofill_manager_->Reset();
  test_ukm_recorder_.Purge();
  autofill_client_.InitializeUKMSources();
}
