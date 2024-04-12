  bool PrepareDcimTestEntries(Profile* profile) {
    if (!CreateRootDirectory(profile))
      return false;

    CreateEntry(AddEntriesMessage::TestEntryInfo(AddEntriesMessage::DIRECTORY,
                                                 "", "DCIM"));
    CreateEntry(AddEntriesMessage::TestEntryInfo(AddEntriesMessage::FILE,
                                                 "image2.png", "image2.png")
                    .SetMimeType("image/png"));
    CreateEntry(AddEntriesMessage::TestEntryInfo(
                    AddEntriesMessage::FILE, "image3.jpg", "DCIM/image3.jpg")
                    .SetMimeType("image/png"));
    CreateEntry(AddEntriesMessage::TestEntryInfo(AddEntriesMessage::FILE,
                                                 "text.txt", "DCIM/hello.txt")
                    .SetMimeType("text/plain"));
    base::RunLoop().RunUntilIdle();
    return true;
  }
