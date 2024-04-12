bool IsKeyEvent(const base::NativeEvent& native_event) {
  return native_event.message == WM_KEYDOWN ||
         native_event.message == WM_SYSKEYDOWN ||
         native_event.message == WM_CHAR ||
         native_event.message == WM_KEYUP ||
         native_event.message == WM_SYSKEYUP;
}
