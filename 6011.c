bool HostNPScriptObject::SetProperty(const std::string& property_name,
                                     const NPVariant* value) {
  VLOG(2) <<  "SetProperty " << property_name;
  CHECK_EQ(base::PlatformThread::CurrentId(), np_thread_id_);

  if (property_name == kAttrNameOnNatTraversalPolicyChanged) {
    if (NPVARIANT_IS_OBJECT(*value)) {
      on_nat_traversal_policy_changed_func_ = NPVARIANT_TO_OBJECT(*value);
      bool policy_received, nat_traversal_enabled;
      {
        base::AutoLock lock(nat_policy_lock_);
        policy_received = policy_received_;
        nat_traversal_enabled = nat_traversal_enabled_;
      }
      if (policy_received) {
        UpdateWebappNatPolicy(nat_traversal_enabled);
      }
      return true;
    } else {
      SetException("SetProperty: unexpected type for property " +
                   property_name);
    }
    return false;
  }

  if (property_name == kAttrNameOnStateChanged) {
    if (NPVARIANT_IS_OBJECT(*value)) {
      on_state_changed_func_ = NPVARIANT_TO_OBJECT(*value);
      return true;
    } else {
      SetException("SetProperty: unexpected type for property " +
                   property_name);
    }
    return false;
  }

  if (property_name == kAttrNameLogDebugInfo) {
    if (NPVARIANT_IS_OBJECT(*value)) {
      log_debug_info_func_ = NPVARIANT_TO_OBJECT(*value);
      HostLogHandler::RegisterLoggingScriptObject(this);
      return true;
    } else {
      SetException("SetProperty: unexpected type for property " +
                   property_name);
    }
    return false;
  }

  return false;
}
