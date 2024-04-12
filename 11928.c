void TabStripModel::UpdateTabContentsStateAt(int index,
    TabStripModelObserver::TabChangeType change_type) {
  DCHECK(ContainsIndex(index));

  FOR_EACH_OBSERVER(TabStripModelObserver, observers_,
      TabChangedAt(GetContentsAt(index), index, change_type));
}
