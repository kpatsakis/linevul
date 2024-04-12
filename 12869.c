bool DirectoryBackingStore::MigrateVersion74To75() {

  if (SQLITE_DONE != ExecQuery(load_dbhandle_,
          "ALTER TABLE models RENAME TO temp_models")) {
    return false;
  }
  if (!CreateModelsTable())
    return false;

  sqlite_utils::SQLStatement query;
  query.prepare(load_dbhandle_,
      "SELECT model_id, last_download_timestamp, initial_sync_ended "
      "FROM temp_models");
  while (SQLITE_ROW == query.step()) {
    ModelType type = ModelIdToModelTypeEnum(query.column_blob(0),
                                            query.column_bytes(0));
    if (type != UNSPECIFIED) {
      sync_pb::DataTypeProgressMarker progress_marker;
      progress_marker.set_data_type_id(
          GetExtensionFieldNumberFromModelType(type));
      progress_marker.set_timestamp_token_for_migration(query.column_int64(1));
      std::string progress_blob;
      progress_marker.SerializeToString(&progress_blob);

      sqlite_utils::SQLStatement update;
      update.prepare(load_dbhandle_, "INSERT INTO models (model_id, "
          "progress_marker, initial_sync_ended) VALUES (?, ?, ?)");
      update.bind_blob(0, query.column_blob(0), query.column_bytes(0));
      update.bind_blob(1, progress_blob.data(), progress_blob.length());
      update.bind_bool(2, query.column_bool(2));
      if (SQLITE_DONE != update.step())
        return false;
    }
  }
  SafeDropTable("temp_models");

  SetVersion(75);
  return true;
}
