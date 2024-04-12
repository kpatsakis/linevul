  void SetProfiles(std::vector<AutofillProfile>* profiles) {
    WindowedPersonalDataManagerObserver observer(browser());
    personal_data_manager()->SetProfiles(profiles);
    observer.Wait();
  }
