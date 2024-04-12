status_t Parcel::readString16Vector(
        std::unique_ptr<std::vector<std::unique_ptr<String16>>>* val) const {
 return readNullableTypedVector(val, &Parcel::readString16);
}
