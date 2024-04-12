void ResourceMessageFilter::OnClipboardIsFormatAvailable(
    Clipboard::FormatType format, Clipboard::Buffer buffer,
    IPC::Message* reply) {
  const bool result = GetClipboard()->IsFormatAvailable(format, buffer);
  ViewHostMsg_ClipboardIsFormatAvailable::WriteReplyParams(reply, result);
  Send(reply);
}
