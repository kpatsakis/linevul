net::NetworkIsolationKey CreateNetworkIsolationKey(const GURL& main_frame_url) {
  url::Origin origin = url::Origin::Create(main_frame_url);
  return net::NetworkIsolationKey(origin, origin);
}
