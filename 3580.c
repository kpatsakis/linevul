static Status UpdateKeyGenerator(IndexedDBBackingStore* backing_store,
                                 IndexedDBTransaction* transaction,
                                 int64_t database_id,
                                 int64_t object_store_id,
                                 const IndexedDBKey& key,
                                 bool check_current) {
  DCHECK_EQ(kWebIDBKeyTypeNumber, key.type());
  const double max_generator_value = 9007199254740992.0;
  int64_t value = base::saturated_cast<int64_t>(
      floor(std::min(key.number(), max_generator_value)));
  return backing_store->MaybeUpdateKeyGeneratorCurrentNumber(
      transaction->BackingStoreTransaction(), database_id, object_store_id,
      value + 1, check_current);
}
