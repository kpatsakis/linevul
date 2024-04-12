  void AddAllUsers() {
    for (size_t i = 0; i < base::size(kTestAccounts); ++i) {
      if (i == PRIMARY_ACCOUNT_INDEX)
        continue;
      AddUser(kTestAccounts[i], i >= SECONDARY_ACCOUNT_INDEX_START);
    }
  }
