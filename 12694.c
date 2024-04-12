ScriptableHandle::~ScriptableHandle() {
  PLUGIN_PRINTF(("ScriptableHandle::~ScriptableHandle (this=%p)\n",
                 static_cast<void*>(this)));
  if (NULL == g_ValidHandles) {
    return;
  }
  g_ValidHandles->erase(this);
  if (desc_handle_ != NULL) {
    PLUGIN_PRINTF(("ScriptableHandle::~ScriptableHandle "
                   "(this=%p, delete desc_handle=%p)\n",
                   static_cast<void*>(this), static_cast<void*>(desc_handle_)));
    delete desc_handle_;
    desc_handle_ = NULL;
  }
  PLUGIN_PRINTF(("ScriptableHandle::~ScriptableHandle (this=%p, return)\n",
                  static_cast<void*>(this)));
}
