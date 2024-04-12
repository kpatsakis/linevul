  MojoAudioOutputStreamTest()
      : foreign_socket_(std::make_unique<TestCancelableSyncSocket>()),
        client_binding_(&client_, mojo::MakeRequest(&client_ptr_)) {}
