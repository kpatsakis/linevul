bool AudioInputRendererHost::OnMessageReceived(const IPC::Message& message,
                                               bool* message_was_ok) {
  bool handled = true;
  IPC_BEGIN_MESSAGE_MAP_EX(AudioInputRendererHost, message, *message_was_ok)
    IPC_MESSAGE_HANDLER(AudioInputHostMsg_StartDevice, OnStartDevice)
    IPC_MESSAGE_HANDLER(AudioInputHostMsg_CreateStream, OnCreateStream)
    IPC_MESSAGE_HANDLER(AudioInputHostMsg_AssociateStreamWithConsumer,
                        OnAssociateStreamWithConsumer)
    IPC_MESSAGE_HANDLER(AudioInputHostMsg_RecordStream, OnRecordStream)
    IPC_MESSAGE_HANDLER(AudioInputHostMsg_CloseStream, OnCloseStream)
    IPC_MESSAGE_HANDLER(AudioInputHostMsg_SetVolume, OnSetVolume)
    IPC_MESSAGE_UNHANDLED(handled = false)
  IPC_END_MESSAGE_MAP_EX()

  return handled;
}
