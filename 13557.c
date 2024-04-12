  explicit OneTimeCachingHostResolver(const HostPortPair& host_port)
      : MockHostResolverBase(/* use_caching = */ true), host_port_(host_port) {}
