DiceTurnSyncOnHelper::DiceTurnSyncOnHelper(
    Profile* profile,
    signin_metrics::AccessPoint signin_access_point,
    signin_metrics::PromoAction signin_promo_action,
    signin_metrics::Reason signin_reason,
    const std::string& account_id,
    SigninAbortedMode signin_aborted_mode,
    std::unique_ptr<Delegate> delegate)
    : delegate_(std::move(delegate)),
      profile_(profile),
      signin_manager_(SigninManagerFactory::GetForProfile(profile)),
      token_service_(ProfileOAuth2TokenServiceFactory::GetForProfile(profile)),
      signin_access_point_(signin_access_point),
      signin_promo_action_(signin_promo_action),
      signin_reason_(signin_reason),
      signin_aborted_mode_(signin_aborted_mode),
      account_info_(GetAccountInfo(profile, account_id)),
      weak_pointer_factory_(this) {
  DCHECK(delegate_);
  DCHECK(profile_);
  DCHECK(!signin_manager_->IsAuthenticated());

  DCHECK(!signin_util::IsForceSigninEnabled());

  if (account_info_.gaia.empty() || account_info_.email.empty()) {
    LOG(ERROR) << "Cannot turn Sync On for invalid account.";
    base::SequencedTaskRunnerHandle::Get()->DeleteSoon(FROM_HERE, this);
    return;
  }

  DCHECK(!account_info_.gaia.empty());
  DCHECK(!account_info_.email.empty());

  if (HasCanOfferSigninError()) {
    base::SequencedTaskRunnerHandle::Get()->PostTask(
        FROM_HERE, base::BindOnce(&DiceTurnSyncOnHelper::AbortAndDelete,
                                  base::Unretained(this)));
    return;
  }

  if (!IsCrossAccountError(profile_, account_info_.email, account_info_.gaia)) {
    TurnSyncOnWithProfileMode(ProfileMode::CURRENT_PROFILE);
    return;
  }

  std::string last_email =
      profile_->GetPrefs()->GetString(prefs::kGoogleServicesLastUsername);
  delegate_->ShowMergeSyncDataConfirmation(
      last_email, account_info_.email,
      base::BindOnce(&DiceTurnSyncOnHelper::OnMergeAccountConfirmation,
                     weak_pointer_factory_.GetWeakPtr()));
}
