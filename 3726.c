  Id Get(int64 metahandle, syncable::IdField field) const {
    return GetField(metahandle, field, syncable::GetNullId());
  }
