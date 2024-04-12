  FactoryForIsolatedMedia(
      const ProfileIOData* profile_io_data,
      const StoragePartitionDescriptor& partition_descriptor,
      ChromeURLRequestContextGetter* app_context)
    : profile_io_data_(profile_io_data),
      partition_descriptor_(partition_descriptor),
      app_context_getter_(app_context) {}
