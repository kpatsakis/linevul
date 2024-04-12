  std::string GetMimeType(const AddEntriesMessage::TestEntryInfo& entry) {
    return entry.type == AddEntriesMessage::FILE
               ? entry.mime_type
               : arc::kAndroidDirectoryMimeType;
  }
