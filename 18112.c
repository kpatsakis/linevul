void OomInterventionTabHelper::DeclineIntervention() {
  RecordInterventionUserDecision(false);
  ResetInterfaces();
  intervention_state_ = InterventionState::DECLINED;

  if (decider_) {
    DCHECK(!web_contents()->GetBrowserContext()->IsOffTheRecord());
    const std::string& host = web_contents()->GetVisibleURL().host();
    decider_->OnInterventionDeclined(host);
  }
}
