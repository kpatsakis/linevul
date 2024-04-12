void LayerTreeHost::SetElementIdsForTesting() {
  LayerTreeHostCommon::CallFunctionForEveryLayer(this, SetElementIdForTesting);
}
