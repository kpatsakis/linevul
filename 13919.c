  void CheckForWaitingLoop() {
    switch (wait_event_) {
      case WaitEvent::kNone:
        return;
      case WaitEvent::kDns:
        if (!HasHostBeenLookedUp(waiting_on_dns_))
          return;
        waiting_on_dns_ = std::string();
        break;
      case WaitEvent::kProxy:
        if (!HasProxyBeenLookedUp(waiting_on_proxy_))
          return;
        waiting_on_proxy_ = GURL();
        break;
    }
    DCHECK(run_loop_);
    run_loop_->Quit();
    run_loop_ = nullptr;
    wait_event_ = WaitEvent::kNone;
  }
