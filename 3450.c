void SocketStream::SetClientSocketFactory(
    ClientSocketFactory* factory) {
  DCHECK(factory);
  factory_ = factory;
}
