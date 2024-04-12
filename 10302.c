    bool appendFileInfo(const File* file, int* index)
    {
        if (!m_blobInfo)
            return false;

        long long size = -1;
        double lastModified = invalidFileTime();
        file->captureSnapshot(size, lastModified);
        *index = m_blobInfo->size();
        m_blobInfo->append(blink::WebBlobInfo(file->uuid(), file->path(), file->name(), file->type(), lastModified, size));
        return true;
    }
