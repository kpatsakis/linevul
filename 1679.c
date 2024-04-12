AeroPeekWindow* AeroPeekManager::GetAeroPeekWindow(int tab_id) const {
  size_t size = tab_list_.size();
  for (std::list<AeroPeekWindow*>::const_iterator i = tab_list_.begin();
       i != tab_list_.end(); ++i) {
    AeroPeekWindow* window = *i;
    if (window->tab_id() == tab_id)
      return window;
  }
  return NULL;
}
