bool HeadlessPrintManager::OnMessageReceived(
    const IPC::Message& message,
    content::RenderFrameHost* render_frame_host) {
  if (!printing_rfh_ &&
      (message.type() == PrintHostMsg_GetDefaultPrintSettings::ID ||
       message.type() == PrintHostMsg_ScriptedPrint::ID)) {
    std::string type;
    switch (message.type()) {
      case PrintHostMsg_GetDefaultPrintSettings::ID:
        type = "GetDefaultPrintSettings";
        break;
      case PrintHostMsg_ScriptedPrint::ID:
        type = "ScriptedPrint";
        break;
      default:
        type = "Unknown";
        break;
    }
    DLOG(ERROR)
        << "Unexpected message received before GetPDFContents is called: "
        << type;

    render_frame_host->Send(IPC::SyncMessage::GenerateReply(&message));
    return true;
  }

  FrameDispatchHelper helper = {this, render_frame_host};
  bool handled = true;
  IPC_BEGIN_MESSAGE_MAP(HeadlessPrintManager, message)
    IPC_MESSAGE_HANDLER(PrintHostMsg_ShowInvalidPrinterSettingsError,
                        OnShowInvalidPrinterSettingsError)
    IPC_MESSAGE_HANDLER(PrintHostMsg_DidPrintDocument, OnDidPrintDocument)
    IPC_MESSAGE_FORWARD_DELAY_REPLY(
        PrintHostMsg_GetDefaultPrintSettings, &helper,
        FrameDispatchHelper::OnGetDefaultPrintSettings)
    IPC_MESSAGE_FORWARD_DELAY_REPLY(PrintHostMsg_ScriptedPrint, &helper,
                                    FrameDispatchHelper::OnScriptedPrint)
    IPC_MESSAGE_UNHANDLED(handled = false)
  IPC_END_MESSAGE_MAP()
  return handled || PrintManager::OnMessageReceived(message, render_frame_host);
}
