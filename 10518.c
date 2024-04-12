 void WebUILoginView::OnLoginPromptVisible() {
   if (should_emit_login_prompt_visible_) {
     chromeos::DBusThreadManager::Get()->GetSessionManagerClient()->
        EmitLoginPromptVisible();
  }

  OobeUI* oobe_ui = static_cast<OobeUI*>(GetWebUI()->GetController());
  oobe_ui->OnLoginPromptVisible();
}
