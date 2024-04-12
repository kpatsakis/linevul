std::string GetUpdatesResponseString(
    const sync_pb::GetUpdatesResponse& response) {
  std::string output;
  output.append("GetUpdatesResponse:\n");
  for (int i = 0; i < response.entries_size(); i++) {
    output.append(SyncerProtoUtil::SyncEntityDebugString(response.entries(i)));
    output.append("\n");
  }
  return output;
}
