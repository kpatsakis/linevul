TabStripGtk::~TabStripGtk() {
  model_->RemoveObserver(this);
  tabstrip_.Destroy();

  std::vector<TabData>::iterator iterator = tab_data_.begin();
  for (; iterator < tab_data_.end(); iterator++) {
    delete iterator->tab;
  }

  tab_data_.clear();

  RemoveMessageLoopObserver();
}
