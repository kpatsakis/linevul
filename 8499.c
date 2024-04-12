  bool PrepareTestEntries(Profile* profile) {
    if (!CreateRootDirectory(profile))
      return false;

    CreateEntry(AddEntriesMessage::TestEntryInfo(AddEntriesMessage::FILE,
                                                 "text.txt", "hello.txt")
                    .SetMimeType("text/plain"));
    CreateEntry(AddEntriesMessage::TestEntryInfo(AddEntriesMessage::DIRECTORY,
                                                 std::string(), "A"));
    base::RunLoop().RunUntilIdle();
    return true;
  }
