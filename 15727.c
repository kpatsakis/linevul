bool HFSBTreeIterator::IsKeyUnexported(const base::string16& key) {
  return key == kHFSDirMetadataFolder ||
         key == kHFSMetadataFolder;
}
