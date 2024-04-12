void BlobStorageContext::OnEnoughSpaceForCopies(const std::string& uuid,
                                                bool success) {
  if (!success) {
    CancelBuildingBlob(uuid, BlobStatus::ERR_OUT_OF_MEMORY);
    return;
  }
  BlobEntry* entry = registry_.GetEntry(uuid);
  if (!entry)
    return;

  if (entry->CanFinishBuilding())
    FinishBuilding(entry);
}
