  string Get(int64 metahandle, syncable::StringField field) {
    return GetField(metahandle, field, string());
  }
