int64 MakeServerNodeForType(UserShare* share,
                            ModelType model_type) {
  sync_pb::EntitySpecifics specifics;
  syncable::AddDefaultExtensionValue(model_type, &specifics);
  syncable::ScopedDirLookup dir(share->dir_manager.get(), share->name);
  EXPECT_TRUE(dir.good());
  syncable::WriteTransaction trans(FROM_HERE, syncable::UNITTEST, dir);
  std::string type_tag = syncable::ModelTypeToRootTag(model_type);
  syncable::Id node_id = syncable::Id::CreateFromServerId(type_tag);
  syncable::MutableEntry entry(&trans, syncable::CREATE_NEW_UPDATE_ITEM,
                               node_id);
  EXPECT_TRUE(entry.good());
  entry.Put(syncable::BASE_VERSION, 1);
  entry.Put(syncable::SERVER_VERSION, 1);
  entry.Put(syncable::IS_UNAPPLIED_UPDATE, false);
  entry.Put(syncable::SERVER_PARENT_ID, syncable::GetNullId());
  entry.Put(syncable::SERVER_IS_DIR, true);
  entry.Put(syncable::IS_DIR, true);
  entry.Put(syncable::SERVER_SPECIFICS, specifics);
  entry.Put(syncable::UNIQUE_SERVER_TAG, type_tag);
  entry.Put(syncable::NON_UNIQUE_NAME, type_tag);
  entry.Put(syncable::IS_DEL, false);
  entry.Put(syncable::SPECIFICS, specifics);
  return entry.Get(syncable::META_HANDLE);
}
