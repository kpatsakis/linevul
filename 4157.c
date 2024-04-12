bool RenderWidgetHostImpl::OnMessageReceived(const IPC::Message &msg) {
  bool handled = true;
  bool msg_is_ok = true;
  IPC_BEGIN_MESSAGE_MAP_EX(RenderWidgetHostImpl, msg, msg_is_ok)
    IPC_MESSAGE_HANDLER(ViewHostMsg_RenderViewReady, OnMsgRenderViewReady)
    IPC_MESSAGE_HANDLER(ViewHostMsg_RenderViewGone, OnMsgRenderViewGone)
    IPC_MESSAGE_HANDLER(ViewHostMsg_Close, OnMsgClose)
    IPC_MESSAGE_HANDLER(ViewHostMsg_UpdateScreenRects_ACK,
                        OnMsgUpdateScreenRectsAck)
    IPC_MESSAGE_HANDLER(ViewHostMsg_RequestMove, OnMsgRequestMove)
    IPC_MESSAGE_HANDLER(ViewHostMsg_SetTooltipText, OnMsgSetTooltipText)
    IPC_MESSAGE_HANDLER(ViewHostMsg_PaintAtSize_ACK, OnMsgPaintAtSizeAck)
    IPC_MESSAGE_HANDLER(ViewHostMsg_CompositorSurfaceBuffersSwapped,
                        OnCompositorSurfaceBuffersSwapped)
    IPC_MESSAGE_HANDLER(ViewHostMsg_UpdateRect, OnMsgUpdateRect)
    IPC_MESSAGE_HANDLER(ViewHostMsg_UpdateIsDelayed, OnMsgUpdateIsDelayed)
    IPC_MESSAGE_HANDLER(ViewHostMsg_HandleInputEvent_ACK, OnMsgInputEventAck)
    IPC_MESSAGE_HANDLER(ViewHostMsg_BeginSmoothScroll, OnMsgBeginSmoothScroll)
    IPC_MESSAGE_HANDLER(ViewHostMsg_SelectRange_ACK, OnMsgSelectRangeAck)
    IPC_MESSAGE_HANDLER(ViewHostMsg_Focus, OnMsgFocus)
    IPC_MESSAGE_HANDLER(ViewHostMsg_Blur, OnMsgBlur)
    IPC_MESSAGE_HANDLER(ViewHostMsg_HasTouchEventHandlers,
                        OnMsgHasTouchEventHandlers)
    IPC_MESSAGE_HANDLER(ViewHostMsg_SetCursor, OnMsgSetCursor)
    IPC_MESSAGE_HANDLER(ViewHostMsg_TextInputStateChanged,
                        OnMsgTextInputStateChanged)
    IPC_MESSAGE_HANDLER(ViewHostMsg_ImeCompositionRangeChanged,
                        OnMsgImeCompositionRangeChanged)
    IPC_MESSAGE_HANDLER(ViewHostMsg_ImeCancelComposition,
                        OnMsgImeCancelComposition)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DidActivateAcceleratedCompositing,
                        OnMsgDidActivateAcceleratedCompositing)
    IPC_MESSAGE_HANDLER(ViewHostMsg_LockMouse, OnMsgLockMouse)
    IPC_MESSAGE_HANDLER(ViewHostMsg_UnlockMouse, OnMsgUnlockMouse)
    IPC_MESSAGE_HANDLER(ViewHostMsg_ShowDisambiguationPopup,
                        OnMsgShowDisambiguationPopup)
#if defined(OS_MACOSX)
    IPC_MESSAGE_HANDLER(ViewHostMsg_PluginFocusChanged,
                        OnMsgPluginFocusChanged)
    IPC_MESSAGE_HANDLER(ViewHostMsg_StartPluginIme,
                        OnMsgStartPluginIme)
    IPC_MESSAGE_HANDLER(ViewHostMsg_AllocateFakePluginWindowHandle,
                        OnAllocateFakePluginWindowHandle)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DestroyFakePluginWindowHandle,
                        OnDestroyFakePluginWindowHandle)
    IPC_MESSAGE_HANDLER(ViewHostMsg_AcceleratedSurfaceSetIOSurface,
                        OnAcceleratedSurfaceSetIOSurface)
    IPC_MESSAGE_HANDLER(ViewHostMsg_AcceleratedSurfaceSetTransportDIB,
                        OnAcceleratedSurfaceSetTransportDIB)
    IPC_MESSAGE_HANDLER(ViewHostMsg_AcceleratedSurfaceBuffersSwapped,
                        OnAcceleratedSurfaceBuffersSwapped)
#endif
#if defined(OS_ANDROID)
    IPC_MESSAGE_HANDLER(ViewHostMsg_UpdateFrameInfo,
                        OnMsgUpdateFrameInfo)
#endif
#if defined(TOOLKIT_GTK)
    IPC_MESSAGE_HANDLER(ViewHostMsg_CreatePluginContainer,
                        OnMsgCreatePluginContainer)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DestroyPluginContainer,
                        OnMsgDestroyPluginContainer)
#endif
#if defined(OS_WIN)
    IPC_MESSAGE_HANDLER(ViewHostMsg_WindowlessPluginDummyWindowCreated,
                        OnWindowlessPluginDummyWindowCreated)
    IPC_MESSAGE_HANDLER(ViewHostMsg_WindowlessPluginDummyWindowDestroyed,
                        OnWindowlessPluginDummyWindowDestroyed)
#endif
#if defined(OS_CHROMEOS)  // http://crbug.com/162981
    IPC_MESSAGE_HANDLER(ViewHostMsg_GetWindowRect, OnMsgGetWindowRect)
    IPC_MESSAGE_HANDLER(ViewHostMsg_GetRootWindowRect, OnMsgGetRootWindowRect)
#endif
    IPC_MESSAGE_UNHANDLED(handled = false)
  IPC_END_MESSAGE_MAP_EX()

  if (!msg_is_ok) {
    RecordAction(UserMetricsAction("BadMessageTerminate_RWH"));
    GetProcess()->ReceivedBadMessage();
  }
  return handled;
}
