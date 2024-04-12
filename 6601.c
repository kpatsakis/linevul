    SetClientControlledStateDelegateFactoryForTest(
        const DelegateFactoryCallback& callback) {
  auto& factory = GetFactoryForTesting();
  factory = callback;
}
