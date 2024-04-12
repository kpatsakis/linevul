TabStripModel::~TabStripModel() {
  FOR_EACH_OBSERVER(TabStripModelObserver, observers_,
                    TabStripModelDeleted());
  STLDeleteElements(&contents_data_);
  order_controller_.reset();
}
