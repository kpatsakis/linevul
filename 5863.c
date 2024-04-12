bool Parcel::readBool() const
{
 return readInt32() != 0;
}
