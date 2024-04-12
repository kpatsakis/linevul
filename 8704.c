OSExchangeData::Provider* OSExchangeData::CreateProvider() {
  return new OSExchangeDataProviderAura();
}
