void LayerTreeHost::BreakSwapPromises(SwapPromise::DidNotSwapReason reason) {
  for (size_t i = 0; i < swap_promise_list_.size(); i++)
    swap_promise_list_[i]->DidNotSwap(reason);
  swap_promise_list_.clear();
}
