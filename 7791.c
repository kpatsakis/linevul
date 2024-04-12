void GuestViewBase::DidAttach(int guest_proxy_routing_id) {
  DCHECK(guest_proxy_routing_id_ == MSG_ROUTING_NONE ||
         guest_proxy_routing_id == guest_proxy_routing_id_);
  guest_proxy_routing_id_ = guest_proxy_routing_id;

  opener_lifetime_observer_.reset();

  SetUpSizing(*attach_params());

  DidAttachToEmbedder();

  embedder_web_contents()->Send(new GuestViewMsg_GuestAttached(
      element_instance_id_,
      guest_proxy_routing_id));

  SendQueuedEvents();
}
