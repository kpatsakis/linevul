    BlobRegistryContext(const KURL& url, PassOwnPtr<BlobData> blobData)
        : url(url.copy())
        , blobData(blobData)
    {
        this->blobData->detachFromCurrentThread();
    }
