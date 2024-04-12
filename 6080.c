void TaskManagerTableModel::GetGroupRangeForItem(int item,
                                                 views::GroupRange* range) {
  TaskManagerModel::GroupRange range_pair =
      model_->GetGroupRangeForResource(item);
  range->start = range_pair.first;
  range->length = range_pair.second;
}
