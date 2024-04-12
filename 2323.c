    BlobRegistryContext(const KURL& url, PassRefPtr<RawData> streamData)
        : url(url.copy())
        , streamData(streamData)
    {
    }
