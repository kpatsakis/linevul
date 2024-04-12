  explicit RemovePasswordsTester(TestingProfile* testing_profile) {
    PasswordStoreFactory::GetInstance()->SetTestingFactoryAndUse(
        testing_profile,
        password_manager::BuildPasswordStore<
            content::BrowserContext,
            testing::NiceMock<password_manager::MockPasswordStore>>);

    store_ = static_cast<password_manager::MockPasswordStore*>(
        PasswordStoreFactory::GetInstance()
            ->GetForProfile(testing_profile, ServiceAccessType::EXPLICIT_ACCESS)
            .get());

    OSCryptMocker::SetUp();
  }
