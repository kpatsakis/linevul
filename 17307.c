void RenderViewImpl::PrintPage(WebLocalFrame* frame) {
  UMA_HISTOGRAM_BOOLEAN("PrintPreview.InitiatedByScript",
                        frame->Top() == frame);

  UMA_HISTOGRAM_BOOLEAN("PrintPreview.OutOfProcessSubframe",
                        frame->Top()->IsWebRemoteFrame());

  RenderFrameImpl::FromWebFrame(frame)->ScriptedPrint(
      GetWidget()->input_handler().handling_input_event());
}
