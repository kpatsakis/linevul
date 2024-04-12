status_t MediaPlayerService::Client::setMetadataFilter(const Parcel& filter)
{
 status_t status;
    media::Metadata::Filter allow, drop;

 if (unmarshallFilter(filter, &allow, &status) &&
        unmarshallFilter(filter, &drop, &status)) {
 Mutex::Autolock lock(mLock);

        mMetadataAllow = allow;
        mMetadataDrop = drop;
 }
 return status;
}
