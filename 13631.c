void ArcVoiceInteractionFrameworkService::ToggleSessionFromUserInteraction() {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);

  if (!InitiateUserInteraction(true /* is_toggle */))
    return;

  mojom::VoiceInteractionFrameworkInstance* framework_instance =
      ARC_GET_INSTANCE_FOR_METHOD(
          arc_bridge_service_->voice_interaction_framework(),
          ToggleVoiceInteractionSession);
  DCHECK(framework_instance);
  framework_instance->ToggleVoiceInteractionSession(IsHomescreenActive());
}
