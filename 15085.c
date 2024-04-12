void PresentationConnection::send(Blob* data, ExceptionState& exceptionState) {
  ASSERT(data);
  if (!canSendMessage(exceptionState))
    return;

  m_messages.append(new Message(data->blobDataHandle()));
  handleMessageQueue();
}
