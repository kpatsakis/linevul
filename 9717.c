    void doWriteFile(const File& file)
    {
        doWriteWebCoreString(file.hasBackingFile() ? file.path() : "");
        doWriteWebCoreString(file.name());
        doWriteWebCoreString(file.webkitRelativePath());
        doWriteWebCoreString(file.uuid());
        doWriteWebCoreString(file.type());

        if (file.hasValidSnapshotMetadata()) {
            doWriteUint32(static_cast<uint8_t>(1));

            long long size;
            double lastModified;
            file.captureSnapshot(size, lastModified);
            doWriteUint64(static_cast<uint64_t>(size));
            doWriteNumber(lastModified);
        } else {
            append(static_cast<uint8_t>(0));
        }
    }
