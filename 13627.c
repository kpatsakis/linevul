StateChangeReason DiscardReasonToStateChangeReason(DiscardReason reason) {
  switch (reason) {
    case DiscardReason::kExternal:
      return StateChangeReason::EXTENSION_INITIATED;
    case DiscardReason::kProactive:
      return StateChangeReason::BROWSER_INITIATED;
    case DiscardReason::kUrgent:
      return StateChangeReason::SYSTEM_MEMORY_PRESSURE;
   }
 }
