void LayerTreeHostImpl::SetElementFilterMutated(
    ElementId element_id,
    ElementListType list_type,
    const FilterOperations& filters) {
  if (list_type == ElementListType::ACTIVE) {
    SetTreeLayerFilterMutated(element_id, active_tree(), filters);
  } else {
    SetTreeLayerFilterMutated(element_id, pending_tree(), filters);
    SetTreeLayerFilterMutated(element_id, recycle_tree(), filters);
  }
}
