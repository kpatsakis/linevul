status_t Parcel::readChar(char16_t *pArg) const
{
 int32_t tmp;
 status_t ret = readInt32(&tmp);
 *pArg = char16_t(tmp);
 return ret;
}
