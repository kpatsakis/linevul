void VRDisplay::OnConnected() {
  navigator_vr_->EnqueueVREvent(VRDisplayEvent::Create(
      EventTypeNames::vrdisplayconnect, true, false, this, "connect"));
}
