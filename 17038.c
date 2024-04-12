void WebViewTestClient::PrintPage(blink::WebLocalFrame* frame) {
  blink::WebSize page_size_in_pixels = frame->View()->Size();
  if (page_size_in_pixels.IsEmpty())
    return;
  blink::WebPrintParams printParams(page_size_in_pixels);
  frame->PrintBegin(printParams);
  frame->PrintEnd();
}
