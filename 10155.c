ModelType DirectoryBackingStore::ModelIdToModelTypeEnum(
    const void* data, int size) {
  sync_pb::EntitySpecifics specifics;
  if (!specifics.ParseFromArray(data, size))
    return syncable::UNSPECIFIED;
  return syncable::GetModelTypeFromSpecifics(specifics);
}
