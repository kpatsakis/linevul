int AddressFlagsToNetAddressAttributes(int flags) {
  int result = 0;
  if (flags & IN6_IFF_TEMPORARY) {
    result |= IP_ADDRESS_ATTRIBUTE_TEMPORARY;
  }
  if (flags & IN6_IFF_DEPRECATED) {
    result |= IP_ADDRESS_ATTRIBUTE_DEPRECATED;
  }
  if (flags & IN6_IFF_ANYCAST) {
    result |= IP_ADDRESS_ATTRIBUTE_ANYCAST;
  }
  if (flags & IN6_IFF_TENTATIVE) {
    result |= IP_ADDRESS_ATTRIBUTE_TENTATIVE;
  }
  if (flags & IN6_IFF_DUPLICATED) {
    result |= IP_ADDRESS_ATTRIBUTE_DUPLICATED;
  }
  if (flags & IN6_IFF_DETACHED) {
    result |= IP_ADDRESS_ATTRIBUTE_DETACHED;
  }
  return result;
}
