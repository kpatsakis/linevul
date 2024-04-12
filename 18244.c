GahpClient::setDelegProxy( Proxy *proxy )
{
	if ( !server->can_cache_proxies ) {
		return;
	}
	if ( deleg_proxy != NULL && proxy == deleg_proxy->proxy ) {
		return;
	}
	if ( deleg_proxy != NULL ) {
		server->UnregisterProxy( deleg_proxy->proxy );
	}
	GahpProxyInfo *gahp_proxy = server->RegisterProxy( proxy );
	ASSERT(gahp_proxy);
	deleg_proxy = gahp_proxy;
}
