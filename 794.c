void AppLauncherHandler::ExtensionEnableFlowFinished() {
  DCHECK_EQ(extension_id_prompting_, extension_enable_flow_->extension_id());

  base::StringValue app_id(extension_id_prompting_);
  web_ui()->CallJavascriptFunction("ntp.launchAppAfterEnable", app_id);

  extension_enable_flow_.reset();
  extension_id_prompting_ = "";
}
