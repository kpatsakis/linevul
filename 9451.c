bool TabLifecycleUnitSource::TabLifecycleUnit::Discard(DiscardReason reason) {
  if (!tab_strip_model_)
    return false;

  const LifecycleUnitState target_state =
      reason == DiscardReason::kProactive &&
              GetState() != LifecycleUnitState::FROZEN
          ? LifecycleUnitState::PENDING_DISCARD
          : LifecycleUnitState::DISCARDED;
  if (!IsValidStateChange(GetState(), target_state,
                          DiscardReasonToStateChangeReason(reason))) {
    return false;
  }

  discard_reason_ = reason;

  if (target_state == LifecycleUnitState::PENDING_DISCARD)
    RequestFreezeForDiscard(reason);
  else
    FinishDiscard(reason);

  return true;
}
