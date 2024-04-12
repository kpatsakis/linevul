void Dispatcher::OnMessageInvoke(const std::string& extension_id,
                                 const std::string& module_name,
                                 const std::string& function_name,
                                 const base::ListValue& args,
                                 bool user_gesture) {
  InvokeModuleSystemMethod(
      NULL, extension_id, module_name, function_name, args, user_gesture);
}
