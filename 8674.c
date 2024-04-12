void ScriptableHandle::Unref(ScriptableHandle** handle) {
  if (*handle != NULL) {
    (*handle)->Unref();
    *handle = NULL;
  }
}
