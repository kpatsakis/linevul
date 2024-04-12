    PassRefPtrWillBeRawPtr<File> readFileIndexHelper()
    {
        if (m_version < 3)
            return nullptr;
        ASSERT(m_blobInfo);
        uint32_t index;
        if (!doReadUint32(&index) || index >= m_blobInfo->size())
            return nullptr;
        const blink::WebBlobInfo& info = (*m_blobInfo)[index];
        return File::createFromIndexedSerialization(info.filePath(), info.fileName(), info.size(), info.lastModified(), getOrCreateBlobDataHandle(info.uuid(), info.type(), info.size()));
    }
