status_t Parcel::readBoolVector(std::unique_ptr<std::vector<bool>>* val) const {
 const int32_t start = dataPosition();
 int32_t size;
 status_t status = readInt32(&size);
    val->reset();

 if (status != OK || size < 0) {
 return status;
 }

    setDataPosition(start);
    val->reset(new (std::nothrow) std::vector<bool>());

    status = readBoolVector(val->get());

 if (status != OK) {
        val->reset();
 }

 return status;
}
