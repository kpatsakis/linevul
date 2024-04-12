uint32_t GetLiveObjectsForInstance(PP_Instance instance_id) {
  return HostGlobals::Get()->GetResourceTracker()->GetLiveObjectsForInstance(
      instance_id);
}
