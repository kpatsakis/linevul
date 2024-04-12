void BrowserRenderProcessHost::ClearTransportDIBCache() {
  STLDeleteContainerPairSecondPointers(
      cached_dibs_.begin(), cached_dibs_.end());
  cached_dibs_.clear();
}
