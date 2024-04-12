StatusOr<uint16_t> convertStringAddress(std::string addr, uint8_t* buffer) {
 if (inet_pton(AF_INET, addr.c_str(), buffer) == 1) {
 return AF_INET;
 } else if (inet_pton(AF_INET6, addr.c_str(), buffer) == 1) {
 return AF_INET6;
 } else {
 return Status(EAFNOSUPPORT);
 }
}
