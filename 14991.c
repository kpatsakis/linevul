ScriptableHandle::ScriptableHandle(DescBasedHandle* desc_handle)
  : var_(NULL), num_unref_calls_(0), plugin_(NULL), desc_handle_(desc_handle) {
  PLUGIN_PRINTF(("ScriptableHandle::ScriptableHandle (this=%p,"
                 " desc_handle=%p)\n",
                 static_cast<void*>(this),
                 static_cast<void*>(desc_handle)));
  RememberValidHandle(this);
  PLUGIN_PRINTF(("ScriptableHandle::ScriptableHandle (this=%p)\n",
                 static_cast<void*>(this)));
}
