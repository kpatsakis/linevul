void SyncTest::TriggerMigrationDoneError(
    syncable::ModelTypeSet model_types) {
  ASSERT_TRUE(ServerSupportsErrorTriggering());
  std::string path = "chromiumsync/migrate";
  char joiner = '?';
  for (syncable::ModelTypeSet::Iterator it = model_types.First();
       it.Good(); it.Inc()) {
    path.append(
        base::StringPrintf(
            "%ctype=%d", joiner,
            syncable::GetSpecificsFieldNumberFromModelType(it.Get())));
    joiner = '&';
  }
  ui_test_utils::NavigateToURL(browser(), sync_server_.GetURL(path));
  ASSERT_EQ("Migration: 200",
            UTF16ToASCII(browser()->GetSelectedWebContents()->GetTitle()));
}
