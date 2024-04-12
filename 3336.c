void DiceTurnSyncOnHelper::CompleteInitForNewProfile(
    Profile* new_profile,
    Profile::CreateStatus status) {
  DCHECK_NE(profile_, new_profile);

  switch (status) {
    case Profile::CREATE_STATUS_LOCAL_FAIL:
      NOTREACHED() << "Error creating new profile";
      AbortAndDelete();
      break;
    case Profile::CREATE_STATUS_CREATED:
      break;
    case Profile::CREATE_STATUS_INITIALIZED:
      delegate_->ShowSigninPageInNewProfile(new_profile, account_info_.email);
      AbortAndDelete();
      break;
    case Profile::CREATE_STATUS_REMOTE_FAIL:
    case Profile::CREATE_STATUS_CANCELED:
    case Profile::MAX_CREATE_STATUS: {
      NOTREACHED() << "Invalid profile creation status";
      AbortAndDelete();
      break;
    }
  }
}
