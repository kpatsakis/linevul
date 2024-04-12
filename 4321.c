void FocusFrame(FrameTreeNode* frame) {
  FrameFocusedObserver focus_observer(frame->current_frame_host());
  SimulateMouseClick(frame->current_frame_host()->GetRenderWidgetHost(), 1, 1);
  focus_observer.Wait();
}
