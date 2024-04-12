void PrintPreviewMessageHandler::OnPrintPreviewCancelled(int document_cookie) {
  StopWorker(document_cookie);
}
