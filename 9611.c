bool WebContentsImpl::OnMessageReceived(RenderViewHostImpl* render_view_host,
                                        const IPC::Message& message) {
  RenderFrameHost* main_frame = render_view_host->GetMainFrame();
  if (main_frame) {
    WebUIImpl* web_ui = static_cast<RenderFrameHostImpl*>(main_frame)->web_ui();
    if (web_ui && web_ui->OnMessageReceived(message))
      return true;
  }

  for (auto& observer : observers_) {
    if (observer.OnMessageReceived(message))
      return true;
  }

  bool handled = true;
  IPC_BEGIN_MESSAGE_MAP_WITH_PARAM(WebContentsImpl, message, render_view_host)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DidFirstVisuallyNonEmptyPaint,
                        OnFirstVisuallyNonEmptyPaint)
    IPC_MESSAGE_HANDLER(ViewHostMsg_GoToEntryAtOffset, OnGoToEntryAtOffset)
    IPC_MESSAGE_HANDLER(ViewHostMsg_UpdateZoomLimits, OnUpdateZoomLimits)
    IPC_MESSAGE_HANDLER(ViewHostMsg_PageScaleFactorChanged,
                        OnPageScaleFactorChanged)
    IPC_MESSAGE_HANDLER(ViewHostMsg_EnumerateDirectory, OnEnumerateDirectory)
    IPC_MESSAGE_HANDLER(ViewHostMsg_AppCacheAccessed, OnAppCacheAccessed)
    IPC_MESSAGE_HANDLER(ViewHostMsg_WebUISend, OnWebUISend)
#if BUILDFLAG(ENABLE_PLUGINS)
    IPC_MESSAGE_HANDLER(ViewHostMsg_RequestPpapiBrokerPermission,
                        OnRequestPpapiBrokerPermission)
#endif
    IPC_MESSAGE_HANDLER(ViewHostMsg_ShowValidationMessage,
                        OnShowValidationMessage)
    IPC_MESSAGE_HANDLER(ViewHostMsg_HideValidationMessage,
                        OnHideValidationMessage)
    IPC_MESSAGE_HANDLER(ViewHostMsg_MoveValidationMessage,
                        OnMoveValidationMessage)
#if defined(OS_ANDROID)
    IPC_MESSAGE_HANDLER(ViewHostMsg_OpenDateTimeDialog, OnOpenDateTimeDialog)
#endif
    IPC_MESSAGE_UNHANDLED(handled = false)
  IPC_END_MESSAGE_MAP()

  return handled;
}
