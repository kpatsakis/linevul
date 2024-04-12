  TestCase& DisableDriveFs() {
    enable_drivefs.emplace(false);
    return *this;
  }
