TreeView::NodeDetails* TreeView::GetNodeDetailsByID(int id) {
  DCHECK(id_to_details_map_.find(id) != id_to_details_map_.end());
  return id_to_details_map_[id];
}
