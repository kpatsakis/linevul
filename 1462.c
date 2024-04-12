bool RenderViewHostImpl::OnMessageReceived(const IPC::Message& msg) {
  if (!BrowserMessageFilter::CheckCanDispatchOnUI(msg, this))
    return true;

  if (is_swapped_out_) {
    if (!SwappedOutMessages::CanHandleWhileSwappedOut(msg)) {
      if (msg.is_sync()) {
        IPC::Message* reply = IPC::SyncMessage::GenerateReply(&msg);
        reply->set_reply_error();
        Send(reply);
      }
      return true;
    }
  }

  ObserverListBase<RenderViewHostObserver>::Iterator it(observers_);
  RenderViewHostObserver* observer;
  while ((observer = it.GetNext()) != NULL) {
    if (observer->OnMessageReceived(msg))
      return true;
  }

  if (delegate_->OnMessageReceived(this, msg))
    return true;

  bool handled = true;
  bool msg_is_ok = true;
  IPC_BEGIN_MESSAGE_MAP_EX(RenderViewHostImpl, msg, msg_is_ok)
    IPC_MESSAGE_HANDLER(ViewHostMsg_ShowView, OnShowView)
    IPC_MESSAGE_HANDLER(ViewHostMsg_ShowWidget, OnShowWidget)
    IPC_MESSAGE_HANDLER(ViewHostMsg_ShowFullscreenWidget,
                        OnShowFullscreenWidget)
    IPC_MESSAGE_HANDLER_DELAY_REPLY(ViewHostMsg_RunModal, OnRunModal)
    IPC_MESSAGE_HANDLER(ViewHostMsg_RenderViewReady, OnRenderViewReady)
    IPC_MESSAGE_HANDLER(ViewHostMsg_RenderViewGone, OnRenderViewGone)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DidStartProvisionalLoadForFrame,
                        OnDidStartProvisionalLoadForFrame)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DidRedirectProvisionalLoad,
                        OnDidRedirectProvisionalLoad)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DidFailProvisionalLoadWithError,
                        OnDidFailProvisionalLoadWithError)
    IPC_MESSAGE_HANDLER_GENERIC(ViewHostMsg_FrameNavigate, OnNavigate(msg))
    IPC_MESSAGE_HANDLER(ViewHostMsg_UpdateState, OnUpdateState)
    IPC_MESSAGE_HANDLER(ViewHostMsg_UpdateTitle, OnUpdateTitle)
    IPC_MESSAGE_HANDLER(ViewHostMsg_UpdateEncoding, OnUpdateEncoding)
    IPC_MESSAGE_HANDLER(ViewHostMsg_UpdateTargetURL, OnUpdateTargetURL)
    IPC_MESSAGE_HANDLER(ViewHostMsg_UpdateInspectorSetting,
                        OnUpdateInspectorSetting)
    IPC_MESSAGE_HANDLER(ViewHostMsg_Close, OnClose)
    IPC_MESSAGE_HANDLER(ViewHostMsg_RequestMove, OnRequestMove)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DidStartLoading, OnDidStartLoading)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DidStopLoading, OnDidStopLoading)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DidChangeLoadProgress,
                        OnDidChangeLoadProgress)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DidDisownOpener, OnDidDisownOpener)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DocumentAvailableInMainFrame,
                        OnDocumentAvailableInMainFrame)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DocumentOnLoadCompletedInMainFrame,
                        OnDocumentOnLoadCompletedInMainFrame)
    IPC_MESSAGE_HANDLER(ViewHostMsg_ContextMenu, OnContextMenu)
    IPC_MESSAGE_HANDLER(ViewHostMsg_ToggleFullscreen, OnToggleFullscreen)
    IPC_MESSAGE_HANDLER(ViewHostMsg_OpenURL, OnOpenURL)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DidContentsPreferredSizeChange,
                        OnDidContentsPreferredSizeChange)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DidChangeScrollbarsForMainFrame,
                        OnDidChangeScrollbarsForMainFrame)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DidChangeScrollOffsetPinningForMainFrame,
                        OnDidChangeScrollOffsetPinningForMainFrame)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DidChangeNumWheelEvents,
                        OnDidChangeNumWheelEvents)
    IPC_MESSAGE_HANDLER(ViewHostMsg_RouteCloseEvent,
                        OnRouteCloseEvent)
    IPC_MESSAGE_HANDLER(ViewHostMsg_RouteMessageEvent, OnRouteMessageEvent)
    IPC_MESSAGE_HANDLER_DELAY_REPLY(ViewHostMsg_RunJavaScriptMessage,
                                    OnRunJavaScriptMessage)
    IPC_MESSAGE_HANDLER_DELAY_REPLY(ViewHostMsg_RunBeforeUnloadConfirm,
                                    OnRunBeforeUnloadConfirm)
    IPC_MESSAGE_HANDLER(DragHostMsg_StartDragging, OnStartDragging)
    IPC_MESSAGE_HANDLER(DragHostMsg_UpdateDragCursor, OnUpdateDragCursor)
    IPC_MESSAGE_HANDLER(DragHostMsg_TargetDrop_ACK, OnTargetDropACK)
    IPC_MESSAGE_HANDLER(ViewHostMsg_TakeFocus, OnTakeFocus)
    IPC_MESSAGE_HANDLER(ViewHostMsg_FocusedNodeChanged, OnFocusedNodeChanged)
    IPC_MESSAGE_HANDLER(ViewHostMsg_AddMessageToConsole, OnAddMessageToConsole)
    IPC_MESSAGE_HANDLER(ViewHostMsg_ShouldClose_ACK, OnShouldCloseACK)
    IPC_MESSAGE_HANDLER(ViewHostMsg_ClosePage_ACK, OnClosePageACK)
    IPC_MESSAGE_HANDLER(ViewHostMsg_SelectionChanged, OnSelectionChanged)
    IPC_MESSAGE_HANDLER(ViewHostMsg_SelectionBoundsChanged,
                        OnSelectionBoundsChanged)
    IPC_MESSAGE_HANDLER(ViewHostMsg_ScriptEvalResponse, OnScriptEvalResponse)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DidZoomURL, OnDidZoomURL)
    IPC_MESSAGE_HANDLER(ViewHostMsg_MediaNotification, OnMediaNotification)
    IPC_MESSAGE_HANDLER(ViewHostMsg_GetWindowSnapshot, OnGetWindowSnapshot)
#if defined(OS_ANDROID)
    IPC_MESSAGE_HANDLER(ViewHostMsg_StartContentIntent, OnStartContentIntent)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DidChangeBodyBackgroundColor,
                        OnDidChangeBodyBackgroundColor)
#endif
    IPC_MESSAGE_HANDLER(DesktopNotificationHostMsg_RequestPermission,
                        OnRequestDesktopNotificationPermission)
    IPC_MESSAGE_HANDLER(DesktopNotificationHostMsg_Show,
                        OnShowDesktopNotification)
    IPC_MESSAGE_HANDLER(DesktopNotificationHostMsg_Cancel,
                        OnCancelDesktopNotification)
#if defined(OS_MACOSX) || defined(OS_ANDROID)
    IPC_MESSAGE_HANDLER(ViewHostMsg_ShowPopup, OnShowPopup)
#endif
    IPC_MESSAGE_HANDLER(ViewHostMsg_RunFileChooser, OnRunFileChooser)
    IPC_MESSAGE_HANDLER(ViewHostMsg_DomOperationResponse,
                        OnDomOperationResponse)
    IPC_MESSAGE_HANDLER(AccessibilityHostMsg_Notifications,
                        OnAccessibilityNotifications)
    IPC_MESSAGE_HANDLER(ViewHostMsg_FrameTreeUpdated, OnFrameTreeUpdated)
    IPC_MESSAGE_UNHANDLED(
        handled = RenderWidgetHostImpl::OnMessageReceived(msg))
  IPC_END_MESSAGE_MAP_EX()

  if (!msg_is_ok) {
    RecordAction(UserMetricsAction("BadMessageTerminate_RVH"));
    GetProcess()->ReceivedBadMessage();
  }

  return handled;
}
