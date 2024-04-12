void H264DPB::RemoveUnused() {
  for (Pictures::iterator it = pics_.begin(); it != pics_.end(); ) {
    if ((*it)->outputted && !(*it)->ref)
      pics_.erase(it++);
    else
      ++it;
  }
}
