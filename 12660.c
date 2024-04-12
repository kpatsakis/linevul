void OneClickSigninSyncStarter::ConfirmAndSignin() {
  SigninManager* signin = SigninManagerFactory::GetForProfile(profile_);
  if (confirmation_required_ == CONFIRM_UNTRUSTED_SIGNIN) {
    EnsureBrowser();
    browser_->window()->ShowOneClickSigninBubble(
        BrowserWindow::ONE_CLICK_SIGNIN_BUBBLE_TYPE_SAML_MODAL_DIALOG,
        UTF8ToUTF16(signin->GetUsernameForAuthInProgress()),
        string16(), // No error message to display.
        base::Bind(&OneClickSigninSyncStarter::UntrustedSigninConfirmed,
                   weak_pointer_factory_.GetWeakPtr()));
  } else {
    signin->CompletePendingSignin();
  }
}
