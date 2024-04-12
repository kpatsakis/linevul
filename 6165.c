    SetGetURLLoaderFactoryForBrowserProcessCallbackForTesting(
        const CreateNetworkFactoryCallback& url_loader_factory_callback) {
  DCHECK(!BrowserThread::IsThreadInitialized(BrowserThread::UI) ||
         BrowserThread::CurrentlyOn(BrowserThread::UI));
  DCHECK(url_loader_factory_callback.is_null() ||
         g_url_loader_factory_callback_for_test.Get().is_null())
      << "It is not expected that this is called with non-null callback when "
      << "another overriding callback is already set.";
  g_url_loader_factory_callback_for_test.Get() = url_loader_factory_callback;
}
