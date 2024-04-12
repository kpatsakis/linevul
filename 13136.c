bool Parcel::hasFileDescriptors() const
{
 if (!mFdsKnown) {
        scanForFds();
 }
 return mHasFds;
}
