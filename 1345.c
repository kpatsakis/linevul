bool PluginModule::ReserveInstanceID(PP_Instance instance) {
  if (reserve_instance_id_)
    return PPBoolToBool(reserve_instance_id_(pp_module_, instance));
  return true;  // Instance ID is usable.
}
