int32 ResourceTracker::AddVar(Var* var) {
  if (last_var_id_ == std::numeric_limits<int32>::max() >> kPPIdTypeBits)
    return 0;

  int32 new_id = MakeTypedId(++last_var_id_, PP_ID_TYPE_VAR);
  live_vars_.insert(std::make_pair(new_id, std::make_pair(var, 1)));

  ObjectVar* object_var = var->AsObjectVar();
  if (object_var) {
    PP_Instance instance = object_var->instance()->pp_instance();
    DCHECK(instance_map_.find(instance) != instance_map_.end());
    instance_map_[instance]->object_vars.insert(new_id);
  }

  return new_id;
}
