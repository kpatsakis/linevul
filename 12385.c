bool OneClickSigninHelper::OnFormSubmitted(const content::PasswordForm& form) {

  if (form.origin.is_valid() &&
      gaia::IsGaiaSignonRealm(GURL(form.signon_realm))) {
    VLOG(1) << "OneClickSigninHelper::DidNavigateAnyFrame: got password";
    password_ = UTF16ToUTF8(form.password_value);
  }

  return true;
}
