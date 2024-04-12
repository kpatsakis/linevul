ZeroSuggestProvider* ZeroSuggestProvider::Create(
    AutocompleteProviderClient* client,
    HistoryURLProvider* history_url_provider,
    AutocompleteProviderListener* listener) {
  return new ZeroSuggestProvider(client, history_url_provider, listener);
}
