status_t Parcel::readBlob(size_t len, ReadableBlob* outBlob) const
{
 int32_t useAshmem;
 status_t status = readInt32(&useAshmem);
 if (status) return status;

 if (!useAshmem) {
        ALOGV("readBlob: read in place");
 const void* ptr = readInplace(len);
 if (!ptr) return BAD_VALUE;

        outBlob->init(false /*mapped*/, const_cast<void*>(ptr), len);
 return NO_ERROR;
 }

    ALOGV("readBlob: read from ashmem");
 int fd = readFileDescriptor();
 if (fd == int(BAD_TYPE)) return BAD_VALUE;

 void* ptr = ::mmap(NULL, len, PROT_READ, MAP_SHARED, fd, 0);
 if (ptr == MAP_FAILED) return NO_MEMORY;

    outBlob->init(true /*mapped*/, ptr, len);
 return NO_ERROR;
}
