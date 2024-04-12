pp::Var Plugin::GetInstanceObject() {
  PLUGIN_PRINTF(("Plugin::GetInstanceObject (this=%p)\n",
                 static_cast<void*>(this)));
  ScriptablePlugin* handle =
      static_cast<ScriptablePlugin*>(scriptable_plugin()->AddRef());
  pp::Var* handle_var = handle->var();
  PLUGIN_PRINTF(("Plugin::GetInstanceObject (handle=%p, handle_var=%p)\n",
                 static_cast<void*>(handle), static_cast<void*>(handle_var)));
  return *handle_var;  // make a copy
}
