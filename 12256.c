LRESULT HWNDMessageHandler::DefWindowProcWithRedrawLock(UINT message,
                                                        WPARAM w_param,
                                                        LPARAM l_param) {
  ScopedRedrawLock lock(this);
  base::WeakPtr<HWNDMessageHandler> ref(weak_factory_.GetWeakPtr());
  LRESULT result = DefWindowProc(hwnd(), message, w_param, l_param);
  if (!ref)
    lock.CancelUnlockOperation();
  return result;
}
