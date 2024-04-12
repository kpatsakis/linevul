    PassRefPtr<BlobDataHandle> getOrCreateBlobDataHandle(const String& uuid, const String& type, long long size = -1)
    {
        BlobDataHandleMap::const_iterator it = m_blobDataHandles.find(uuid);
        if (it != m_blobDataHandles.end()) {
            return it->value;
        }
        return BlobDataHandle::create(uuid, type, size);
    }
