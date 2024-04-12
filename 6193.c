void OomInterventionTabHelper::DeclineInterventionWithReload() {
  web_contents()->GetController().Reload(content::ReloadType::NORMAL, true);
  DeclineIntervention();
}
