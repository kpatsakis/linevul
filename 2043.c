void Job::StartCreateV8Resolver(
    const scoped_refptr<ProxyResolverScriptData>& script_data,
    scoped_ptr<ProxyResolverV8>* resolver,
    const CompletionCallback& callback) {
  CheckIsOnOriginThread();

  resolver_out_ = resolver;
  script_data_ = script_data;

  Start(CREATE_V8_RESOLVER, true /*blocking*/, callback);
}
