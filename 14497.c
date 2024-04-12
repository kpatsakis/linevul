bool HFSBTreeIterator::Init(ReadStream* stream) {
  DCHECK(!stream_);
  stream_ = stream;

  if (stream_->Seek(0, SEEK_SET) != 0) {
    DLOG(ERROR) << "Failed to seek to header node";
    return false;
  }

  BTNodeDescriptor node;
  if (!stream_->ReadType(&node)) {
    DLOG(ERROR) << "Failed to read BTNodeDescriptor";
    return false;
  }
  ConvertBigEndian(&node);

  if (node.kind != kBTHeaderNode) {
    DLOG(ERROR) << "Initial node is not a header node";
    return false;
  }

  if (!stream_->ReadType(&header_)) {
    DLOG(ERROR) << "Failed to read BTHeaderRec";
    return false;
  }
  ConvertBigEndian(&header_);

  current_leaf_number_ = header_.firstLeafNode;
  leaf_data_.resize(header_.nodeSize);

  return true;
}
