void ScriptableHandle::Unref() {
  CHECK(++num_unref_calls_ == 1);
  PLUGIN_PRINTF(("ScriptableHandle::Unref (this=%p, var=%p)\n",
                 static_cast<void*>(this), static_cast<void*>(var_)));
  if (var_ != NULL) {
    PLUGIN_PRINTF(("ScriptableHandle::Unref (delete var)\n"));
    pp::Var* var = var_;
    var_ = NULL;
    delete var;
  } else {
    PLUGIN_PRINTF(("ScriptableHandle::Unref (delete this)\n"));
    CHECK(var_ == NULL);
    delete this;
  }
}
