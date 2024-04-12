bool RenderMessageFilter::OnMessageReceived(const IPC::Message& message,
                                            bool* message_was_ok) {
  bool handled = true;
  IPC_BEGIN_MESSAGE_MAP_EX(RenderMessageFilter, message, *message_was_ok)
#if defined(OS_WIN)
    IPC_MESSAGE_HANDLER(ViewHostMsg_PreCacheFontCharacters,
                        OnPreCacheFontCharacters)
#endif
    IPC_MESSAGE_HANDLER(ViewHostMsg_GenerateRoutingID, OnGenerateRoutingID)
    IPC_MESSAGE_HANDLER(ViewHostMsg_CreateWindow, OnCreateWindow)
    IPC_MESSAGE_HANDLER(ViewHostMsg_CreateWidget, OnCreateWidget)
    IPC_MESSAGE_HANDLER(ViewHostMsg_CreateFullscreenWidget,
                        OnCreateFullscreenWidget)
    IPC_MESSAGE_HANDLER(ViewHostMsg_SetCookie, OnSetCookie)
    IPC_MESSAGE_HANDLER_DELAY_REPLY(ViewHostMsg_GetCookies, OnGetCookies)
    IPC_MESSAGE_HANDLER_DELAY_REPLY(ViewHostMsg_GetRawCookies, OnGetRawCookies)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DeleteCookie, OnDeleteCookie)
    IPC_MESSAGE_HANDLER(ViewHostMsg_CookiesEnabled, OnCookiesEnabled)
#if defined(OS_MACOSX)
    IPC_MESSAGE_HANDLER_DELAY_REPLY(ViewHostMsg_LoadFont, OnLoadFont)
#endif
    IPC_MESSAGE_HANDLER(ViewHostMsg_DownloadUrl, OnDownloadUrl)
#if defined(ENABLE_PLUGINS)
    IPC_MESSAGE_HANDLER_DELAY_REPLY(ViewHostMsg_GetPlugins, OnGetPlugins)
    IPC_MESSAGE_HANDLER(ViewHostMsg_GetPluginInfo, OnGetPluginInfo)
    IPC_MESSAGE_HANDLER_DELAY_REPLY(ViewHostMsg_OpenChannelToPlugin,
                                    OnOpenChannelToPlugin)
    IPC_MESSAGE_HANDLER_DELAY_REPLY(ViewHostMsg_OpenChannelToPepperPlugin,
                                    OnOpenChannelToPepperPlugin)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DidCreateOutOfProcessPepperInstance,
                        OnDidCreateOutOfProcessPepperInstance)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DidDeleteOutOfProcessPepperInstance,
                        OnDidDeleteOutOfProcessPepperInstance)
    IPC_MESSAGE_HANDLER(ViewHostMsg_OpenChannelToPpapiBroker,
                        OnOpenChannelToPpapiBroker)
#endif
    IPC_MESSAGE_HANDLER_GENERIC(ViewHostMsg_UpdateRect,
        render_widget_helper_->DidReceiveBackingStoreMsg(message))
    IPC_MESSAGE_HANDLER(ViewHostMsg_UpdateIsDelayed, OnUpdateIsDelayed)
    IPC_MESSAGE_HANDLER(DesktopNotificationHostMsg_CheckPermission,
                        OnCheckNotificationPermission)
    IPC_MESSAGE_HANDLER(ChildProcessHostMsg_SyncAllocateSharedMemory,
                        OnAllocateSharedMemory)
#if defined(OS_MACOSX)
    IPC_MESSAGE_HANDLER(ViewHostMsg_AllocTransportDIB, OnAllocTransportDIB)
    IPC_MESSAGE_HANDLER(ViewHostMsg_FreeTransportDIB, OnFreeTransportDIB)
#endif
    IPC_MESSAGE_HANDLER(ViewHostMsg_DidGenerateCacheableMetadata,
                        OnCacheableMetadataAvailable)
    IPC_MESSAGE_HANDLER_DELAY_REPLY(ViewHostMsg_Keygen, OnKeygen)
    IPC_MESSAGE_HANDLER(ViewHostMsg_AsyncOpenFile, OnAsyncOpenFile)
    IPC_MESSAGE_HANDLER(ViewHostMsg_GetCPUUsage, OnGetCPUUsage)
    IPC_MESSAGE_HANDLER(ViewHostMsg_GetHardwareBufferSize,
                        OnGetHardwareBufferSize)
    IPC_MESSAGE_HANDLER(ViewHostMsg_GetHardwareInputSampleRate,
                        OnGetHardwareInputSampleRate)
    IPC_MESSAGE_HANDLER(ViewHostMsg_GetHardwareSampleRate,
                        OnGetHardwareSampleRate)
    IPC_MESSAGE_HANDLER(ViewHostMsg_GetHardwareInputChannelLayout,
                        OnGetHardwareInputChannelLayout)
    IPC_MESSAGE_HANDLER(ViewHostMsg_GetMonitorColorProfile,
                        OnGetMonitorColorProfile)
    IPC_MESSAGE_HANDLER(ViewHostMsg_MediaLogEvent, OnMediaLogEvent)
    IPC_MESSAGE_HANDLER(ViewHostMsg_Are3DAPIsBlocked, OnAre3DAPIsBlocked)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DidLose3DContext, OnDidLose3DContext)
    IPC_MESSAGE_UNHANDLED(handled = false)
  IPC_END_MESSAGE_MAP_EX()

  return handled;
}
