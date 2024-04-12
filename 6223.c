  void Run() {
    if (!loader_)
      return;
    ExecutionContext& context = loader_->GetElement()->GetDocument();
    probe::AsyncTask async_task(&context, this);
    if (script_state_->ContextIsValid()) {
      ScriptState::Scope scope(script_state_.get());
      loader_->DoUpdateFromElement(should_bypass_main_world_csp_,
                                   update_behavior_, request_url_,
                                   referrer_policy_);
    } else {
      loader_->DoUpdateFromElement(should_bypass_main_world_csp_,
                                   update_behavior_, request_url_,
                                   referrer_policy_);
    }
  }
