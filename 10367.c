void ChromotingInstance::FetchSecretFromDialog(
    bool pairing_supported,
    const protocol::SecretFetchedCallback& secret_fetched_callback) {
  DCHECK(secret_fetched_callback_.is_null());
  secret_fetched_callback_ = secret_fetched_callback;
  scoped_ptr<base::DictionaryValue> data(new base::DictionaryValue());
  data->SetBoolean("pairingSupported", pairing_supported);
  PostLegacyJsonMessage("fetchPin", data.Pass());
}
