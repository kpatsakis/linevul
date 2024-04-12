void LayerTreeHost::SetNeedsAnimate() {
  proxy_->SetNeedsAnimate();
  swap_promise_manager_.NotifySwapPromiseMonitorsOfSetNeedsCommit();
}
