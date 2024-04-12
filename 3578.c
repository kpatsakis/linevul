InputMethodBase::~InputMethodBase() {
  FOR_EACH_OBSERVER(InputMethodObserver,
                    observer_list_,
                    OnInputMethodDestroyed(this));
}
