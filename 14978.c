MetadataRetrieverClient::~MetadataRetrieverClient()
{
    ALOGV("MetadataRetrieverClient destructor");
    disconnect();
}
