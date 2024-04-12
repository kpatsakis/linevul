void DiceResponseHandler::DeleteTokenFetcher(DiceTokenFetcher* token_fetcher) {
  for (auto it = token_fetchers_.begin(); it != token_fetchers_.end(); ++it) {
    if (it->get() == token_fetcher) {
      token_fetchers_.erase(it);
      return;
    }
  }
  NOTREACHED();
}
