bool WebContentsImpl::OnMessageReceived(RenderFrameHostImpl* render_frame_host,
                                        const IPC::Message& message) {
  {
    WebUIImpl* web_ui = render_frame_host->web_ui();
    if (web_ui && web_ui->OnMessageReceived(message, render_frame_host))
      return true;
  }

  for (auto& observer : observers_) {
    if (observer.OnMessageReceived(message, render_frame_host))
      return true;
  }

  bool handled = true;
  IPC_BEGIN_MESSAGE_MAP_WITH_PARAM(WebContentsImpl, message, render_frame_host)
    IPC_MESSAGE_HANDLER(FrameHostMsg_DomOperationResponse,
                        OnDomOperationResponse)
    IPC_MESSAGE_HANDLER(FrameHostMsg_DidChangeThemeColor,
                        OnThemeColorChanged)
    IPC_MESSAGE_HANDLER(FrameHostMsg_DidFinishDocumentLoad,
                        OnDocumentLoadedInFrame)
    IPC_MESSAGE_HANDLER(FrameHostMsg_DidFinishLoad, OnDidFinishLoad)
    IPC_MESSAGE_HANDLER(FrameHostMsg_DidLoadResourceFromMemoryCache,
                        OnDidLoadResourceFromMemoryCache)
    IPC_MESSAGE_HANDLER(FrameHostMsg_DidDisplayInsecureContent,
                        OnDidDisplayInsecureContent)
    IPC_MESSAGE_HANDLER(FrameHostMsg_DidContainInsecureFormAction,
                        OnDidContainInsecureFormAction)
    IPC_MESSAGE_HANDLER(FrameHostMsg_DidRunInsecureContent,
                        OnDidRunInsecureContent)
    IPC_MESSAGE_HANDLER(FrameHostMsg_DidDisplayContentWithCertificateErrors,
                        OnDidDisplayContentWithCertificateErrors)
    IPC_MESSAGE_HANDLER(FrameHostMsg_DidRunContentWithCertificateErrors,
                        OnDidRunContentWithCertificateErrors)
    IPC_MESSAGE_HANDLER(FrameHostMsg_RegisterProtocolHandler,
                        OnRegisterProtocolHandler)
    IPC_MESSAGE_HANDLER(FrameHostMsg_UnregisterProtocolHandler,
                        OnUnregisterProtocolHandler)
    IPC_MESSAGE_HANDLER(FrameHostMsg_UpdatePageImportanceSignals,
                        OnUpdatePageImportanceSignals)
    IPC_MESSAGE_HANDLER(FrameHostMsg_Find_Reply, OnFindReply)
    IPC_MESSAGE_HANDLER(FrameHostMsg_UpdateFaviconURL, OnUpdateFaviconURL)
#if BUILDFLAG(ENABLE_PLUGINS)
    IPC_MESSAGE_HANDLER(FrameHostMsg_PepperInstanceCreated,
                        OnPepperInstanceCreated)
    IPC_MESSAGE_HANDLER(FrameHostMsg_PepperInstanceDeleted,
                        OnPepperInstanceDeleted)
    IPC_MESSAGE_HANDLER(FrameHostMsg_PepperPluginHung, OnPepperPluginHung)
    IPC_MESSAGE_HANDLER(FrameHostMsg_PepperStartsPlayback,
                        OnPepperStartsPlayback)
    IPC_MESSAGE_HANDLER(FrameHostMsg_PepperStopsPlayback,
                        OnPepperStopsPlayback)
    IPC_MESSAGE_HANDLER(FrameHostMsg_PluginCrashed, OnPluginCrashed)
    IPC_MESSAGE_HANDLER_GENERIC(BrowserPluginHostMsg_Attach,
                                OnBrowserPluginMessage(render_frame_host,
                                                       message))
#endif
#if defined(OS_ANDROID)
    IPC_MESSAGE_HANDLER(FrameHostMsg_FindMatchRects_Reply,
                        OnFindMatchRectsReply)
    IPC_MESSAGE_HANDLER(FrameHostMsg_GetNearestFindResult_Reply,
                        OnGetNearestFindResultReply)
#endif
    IPC_MESSAGE_UNHANDLED(handled = false)
  IPC_END_MESSAGE_MAP()

  return handled;
}
