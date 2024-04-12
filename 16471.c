std::unique_ptr<KeyedService> TestingDomainReliabilityServiceFactoryFunction(
    content::BrowserContext* context) {
  const void* kKey = TestingDomainReliabilityServiceFactoryUserData::kKey;

  TestingDomainReliabilityServiceFactoryUserData* data =
      static_cast<TestingDomainReliabilityServiceFactoryUserData*>(
          context->GetUserData(kKey));
  EXPECT_TRUE(data);
  EXPECT_EQ(data->context, context);
  EXPECT_FALSE(data->attached);

  data->attached = true;
  return base::WrapUnique(data->service);
}
