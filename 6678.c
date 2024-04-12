void GuestViewBase::LoadURLWithParams(
      const content::NavigationController::LoadURLParams& load_params) {
  int guest_proxy_routing_id = host()->LoadURLWithParams(load_params);
  DCHECK(guest_proxy_routing_id_ == MSG_ROUTING_NONE ||
         guest_proxy_routing_id == guest_proxy_routing_id_);
  guest_proxy_routing_id_ = guest_proxy_routing_id;
}
