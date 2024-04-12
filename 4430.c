ResourceTracker* ResourceTracker::Get() {
  if (singleton_override_)
    return singleton_override_;
  if (!global_tracker_)
    global_tracker_ = new ResourceTracker;
   return global_tracker_;
 }
