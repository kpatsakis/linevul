void ArcVoiceInteractionFrameworkService::OnConnectionReady() {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);

  if (is_request_pending_) {
    is_request_pending_ = false;
    if (is_pending_request_toggle_) {
      mojom::VoiceInteractionFrameworkInstance* framework_instance =
          ARC_GET_INSTANCE_FOR_METHOD(
              arc_bridge_service_->voice_interaction_framework(),
              ToggleVoiceInteractionSession);
      DCHECK(framework_instance);
      framework_instance->ToggleVoiceInteractionSession(IsHomescreenActive());
    } else {
      mojom::VoiceInteractionFrameworkInstance* framework_instance =
          ARC_GET_INSTANCE_FOR_METHOD(
              arc_bridge_service_->voice_interaction_framework(),
              StartVoiceInteractionSession);
      DCHECK(framework_instance);
      framework_instance->StartVoiceInteractionSession(IsHomescreenActive());
    }
  }

  highlighter_client_->Attach();
}
