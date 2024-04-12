bool RenderViewImpl::OnMessageReceived(const IPC::Message& message) {
  WebFrame* main_frame = webview() ? webview()->mainFrame() : NULL;
  if (main_frame)
    content::GetContentClient()->SetActiveURL(main_frame->document().url());

  ObserverListBase<RenderViewObserver>::Iterator it(observers_);
  RenderViewObserver* observer;
  while ((observer = it.GetNext()) != NULL)
    if (observer->OnMessageReceived(message))
      return true;

  bool handled = true;
  bool msg_is_ok = true;
  IPC_BEGIN_MESSAGE_MAP_EX(RenderViewImpl, message, msg_is_ok)
    IPC_MESSAGE_HANDLER(ViewMsg_Navigate, OnNavigate)
    IPC_MESSAGE_HANDLER(ViewMsg_Stop, OnStop)
    IPC_MESSAGE_HANDLER(ViewMsg_ReloadFrame, OnReloadFrame)
    IPC_MESSAGE_HANDLER(ViewMsg_Undo, OnUndo)
    IPC_MESSAGE_HANDLER(ViewMsg_Redo, OnRedo)
    IPC_MESSAGE_HANDLER(ViewMsg_Cut, OnCut)
    IPC_MESSAGE_HANDLER(ViewMsg_Copy, OnCopy)
#if defined(OS_MACOSX)
    IPC_MESSAGE_HANDLER(ViewMsg_CopyToFindPboard, OnCopyToFindPboard)
#endif
    IPC_MESSAGE_HANDLER(ViewMsg_Paste, OnPaste)
    IPC_MESSAGE_HANDLER(ViewMsg_PasteAndMatchStyle, OnPasteAndMatchStyle)
    IPC_MESSAGE_HANDLER(ViewMsg_Replace, OnReplace)
    IPC_MESSAGE_HANDLER(ViewMsg_Delete, OnDelete)
    IPC_MESSAGE_HANDLER(ViewMsg_SelectAll, OnSelectAll)
    IPC_MESSAGE_HANDLER(ViewMsg_SelectRange, OnSelectRange)
    IPC_MESSAGE_HANDLER(ViewMsg_CopyImageAt, OnCopyImageAt)
    IPC_MESSAGE_HANDLER(ViewMsg_ExecuteEditCommand, OnExecuteEditCommand)
    IPC_MESSAGE_HANDLER(ViewMsg_Find, OnFind)
    IPC_MESSAGE_HANDLER(ViewMsg_StopFinding, OnStopFinding)
    IPC_MESSAGE_HANDLER(ViewMsg_FindReplyACK, OnFindReplyAck)
    IPC_MESSAGE_HANDLER(ViewMsg_Zoom, OnZoom)
    IPC_MESSAGE_HANDLER(ViewMsg_SetZoomLevel, OnSetZoomLevel)
    IPC_MESSAGE_HANDLER(ViewMsg_ZoomFactor, OnZoomFactor)
    IPC_MESSAGE_HANDLER(ViewMsg_SetZoomLevelForLoadingURL,
                        OnSetZoomLevelForLoadingURL)
    IPC_MESSAGE_HANDLER(ViewMsg_SetPageEncoding, OnSetPageEncoding)
    IPC_MESSAGE_HANDLER(ViewMsg_ResetPageEncodingToDefault,
                        OnResetPageEncodingToDefault)
    IPC_MESSAGE_HANDLER(ViewMsg_ScriptEvalRequest, OnScriptEvalRequest)
    IPC_MESSAGE_HANDLER(ViewMsg_CSSInsertRequest, OnCSSInsertRequest)
    IPC_MESSAGE_HANDLER(DragMsg_TargetDragEnter, OnDragTargetDragEnter)
    IPC_MESSAGE_HANDLER(DragMsg_TargetDragOver, OnDragTargetDragOver)
    IPC_MESSAGE_HANDLER(DragMsg_TargetDragLeave, OnDragTargetDragLeave)
    IPC_MESSAGE_HANDLER(DragMsg_TargetDrop, OnDragTargetDrop)
    IPC_MESSAGE_HANDLER(DragMsg_SourceEndedOrMoved, OnDragSourceEndedOrMoved)
    IPC_MESSAGE_HANDLER(DragMsg_SourceSystemDragEnded,
                        OnDragSourceSystemDragEnded)
    IPC_MESSAGE_HANDLER(ViewMsg_AllowBindings, OnAllowBindings)
    IPC_MESSAGE_HANDLER(ViewMsg_SetWebUIProperty, OnSetWebUIProperty)
    IPC_MESSAGE_HANDLER(ViewMsg_SetInitialFocus, OnSetInitialFocus)
    IPC_MESSAGE_HANDLER(ViewMsg_ScrollFocusedEditableNodeIntoRect,
                        OnScrollFocusedEditableNodeIntoRect)
    IPC_MESSAGE_HANDLER(ViewMsg_UpdateTargetURL_ACK, OnUpdateTargetURLAck)
    IPC_MESSAGE_HANDLER(ViewMsg_UpdateWebPreferences, OnUpdateWebPreferences)
    IPC_MESSAGE_HANDLER(ViewMsg_SetAltErrorPageURL, OnSetAltErrorPageURL)
    IPC_MESSAGE_HANDLER(ViewMsg_EnumerateDirectoryResponse,
                        OnEnumerateDirectoryResponse)
    IPC_MESSAGE_HANDLER(ViewMsg_RunFileChooserResponse, OnFileChooserResponse)
    IPC_MESSAGE_HANDLER(ViewMsg_ShouldClose, OnShouldClose)
    IPC_MESSAGE_HANDLER(ViewMsg_SwapOut, OnSwapOut)
    IPC_MESSAGE_HANDLER(ViewMsg_ClosePage, OnClosePage)
    IPC_MESSAGE_HANDLER(ViewMsg_ThemeChanged, OnThemeChanged)
    IPC_MESSAGE_HANDLER(ViewMsg_DisassociateFromPopupCount,
                        OnDisassociateFromPopupCount)
    IPC_MESSAGE_HANDLER(ViewMsg_MoveOrResizeStarted, OnMoveOrResizeStarted)
    IPC_MESSAGE_HANDLER(ViewMsg_ClearFocusedNode, OnClearFocusedNode)
    IPC_MESSAGE_HANDLER(ViewMsg_SetBackground, OnSetBackground)
    IPC_MESSAGE_HANDLER(ViewMsg_EnablePreferredSizeChangedMode,
                        OnEnablePreferredSizeChangedMode)
    IPC_MESSAGE_HANDLER(ViewMsg_EnableAutoResize, OnEnableAutoResize)
    IPC_MESSAGE_HANDLER(ViewMsg_DisableAutoResize, OnDisableAutoResize)
    IPC_MESSAGE_HANDLER(ViewMsg_DisableScrollbarsForSmallWindows,
                        OnDisableScrollbarsForSmallWindows)
    IPC_MESSAGE_HANDLER(ViewMsg_SetRendererPrefs, OnSetRendererPrefs)
    IPC_MESSAGE_HANDLER(ViewMsg_MediaPlayerActionAt, OnMediaPlayerActionAt)
    IPC_MESSAGE_HANDLER(ViewMsg_PluginActionAt, OnPluginActionAt)
    IPC_MESSAGE_HANDLER(ViewMsg_SetActive, OnSetActive)
    IPC_MESSAGE_HANDLER(ViewMsg_SetNavigationStartTime,
                        OnSetNavigationStartTime)
#if defined(OS_MACOSX)
    IPC_MESSAGE_HANDLER(ViewMsg_SetWindowVisibility, OnSetWindowVisibility)
    IPC_MESSAGE_HANDLER(ViewMsg_WindowFrameChanged, OnWindowFrameChanged)
    IPC_MESSAGE_HANDLER(ViewMsg_PluginImeCompositionCompleted,
                        OnPluginImeCompositionCompleted)
#endif
    IPC_MESSAGE_HANDLER(ViewMsg_SetEditCommandsForNextKeyEvent,
                        OnSetEditCommandsForNextKeyEvent)
    IPC_MESSAGE_HANDLER(ViewMsg_CustomContextMenuAction,
                        OnCustomContextMenuAction)
    IPC_MESSAGE_HANDLER(ViewMsg_AsyncOpenFile_ACK, OnAsyncFileOpened)
    IPC_MESSAGE_HANDLER(ViewMsg_PpapiBrokerChannelCreated,
                        OnPpapiBrokerChannelCreated)
    IPC_MESSAGE_HANDLER(ViewMsg_GetAllSavableResourceLinksForCurrentPage,
                        OnGetAllSavableResourceLinksForCurrentPage)
    IPC_MESSAGE_HANDLER(
        ViewMsg_GetSerializedHtmlDataForCurrentPageWithLocalLinks,
        OnGetSerializedHtmlDataForCurrentPageWithLocalLinks)
#if defined(OS_MACOSX)
    IPC_MESSAGE_HANDLER(ViewMsg_SelectPopupMenuItem, OnSelectPopupMenuItem)
#endif
    IPC_MESSAGE_HANDLER(ViewMsg_ContextMenuClosed, OnContextMenuClosed)
#if defined(ENABLE_FLAPPER_HACKS)
    IPC_MESSAGE_HANDLER(PepperMsg_ConnectTcpACK, OnConnectTcpACK)
#endif
#if defined(OS_MACOSX)
    IPC_MESSAGE_HANDLER(ViewMsg_SetInLiveResize, OnSetInLiveResize)
#endif
    IPC_MESSAGE_HANDLER(ViewMsg_SetHistoryLengthAndPrune,
                        OnSetHistoryLengthAndPrune)
    IPC_MESSAGE_HANDLER(ViewMsg_EnableViewSourceMode, OnEnableViewSourceMode)
    IPC_MESSAGE_HANDLER(JavaBridgeMsg_Init, OnJavaBridgeInit)

    IPC_MESSAGE_UNHANDLED(handled = RenderWidget::OnMessageReceived(message))
  IPC_END_MESSAGE_MAP()

  if (!msg_is_ok) {
    CHECK(false) << "Unable to deserialize message in RenderViewImpl.";
  }

  return handled;
}
