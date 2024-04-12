  ProfilingClientBinder()
      : memlog_client_(), request_(mojo::MakeRequest(&memlog_client_)) {}
