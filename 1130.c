status_t Parcel::writeByteVector(const std::vector<uint8_t>& val) {
 return writeByteVectorInternal(this, val);
}
