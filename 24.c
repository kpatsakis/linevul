void SocketStream::Close() {
  DCHECK(base::MessageLoop::current())
      << "The current base::MessageLoop must exist";
  DCHECK_EQ(base::MessageLoop::TYPE_IO, base::MessageLoop::current()->type())
      << "The current base::MessageLoop must be TYPE_IO";
  if (next_state_ == STATE_NONE)
    return;
  base::MessageLoop::current()->PostTask(
      FROM_HERE, base::Bind(&SocketStream::DoClose, this));
}
