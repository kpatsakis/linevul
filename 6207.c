void CheckConfigsCountForClient(const scoped_refptr<PlatformSensor>& sensor,
                                PlatformSensor::Client* client,
                                size_t expected_count) {
  auto client_entry = sensor->GetConfigMapForTesting().find(client);
  if (sensor->GetConfigMapForTesting().end() == client_entry) {
    EXPECT_EQ(0u, expected_count);
    return;
  }
  EXPECT_EQ(expected_count, client_entry->second.size());
}
