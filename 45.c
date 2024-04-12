void RemoveMockTransaction(const MockTransaction* trans) {
  mock_transactions.erase(GURL(trans->url).spec());
}
