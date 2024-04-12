ChromeURLRequestContextGetter::CreateOffTheRecordForIsolatedApp(
    Profile* profile,
    const ProfileIOData* profile_io_data,
    const StoragePartitionDescriptor& partition_descriptor,
    scoped_ptr<ProtocolHandlerRegistry::JobInterceptorFactory>
        protocol_handler_interceptor,
    content::ProtocolHandlerMap* protocol_handlers) {
  DCHECK(profile->IsOffTheRecord());
  ChromeURLRequestContextGetter* main_context =
      static_cast<ChromeURLRequestContextGetter*>(profile->GetRequestContext());
  return new ChromeURLRequestContextGetter(
      new FactoryForIsolatedApp(profile_io_data, partition_descriptor,
                                main_context,
                                protocol_handler_interceptor.Pass(),
                                protocol_handlers));
}
