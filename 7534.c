bool ChromeContentBrowserClient::IsWebUIAllowedToMakeNetworkRequests(
    const url::Origin& origin) {
  return ChromeWebUIControllerFactory::IsWebUIAllowedToMakeNetworkRequests(
      origin);
}
