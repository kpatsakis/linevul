Container::Container(WEBP_MetaHandler* handler) : Chunk(NULL, handler)
{
    this->needsRewrite = false;

    XMP_IO* file = handler->parent->ioRef;

    file->Seek(12, kXMP_SeekFromStart);

    XMP_Int64 size = handler->initialFileSize;

    XMP_Uns32 peek = 0;

    while (file->Offset() < size) {
        peek = XIO::PeekUns32_LE(file);
        switch (peek) {
        case kChunk_XMP_:
            this->addChunk(new XMPChunk(this, handler));
            break;
        case kChunk_VP8X:
            this->addChunk(new VP8XChunk(this, handler));
            break;
        default:
            this->addChunk(new Chunk(this, handler));
            break;
        }
    }

    if (this->chunks[WEBP_CHUNK_IMAGE].size() == 0) {
        XMP_Throw("File has no image bitstream", kXMPErr_BadFileFormat);
    }

    if (this->chunks[WEBP_CHUNK_VP8X].size() == 0) {
        this->needsRewrite = true;
        this->addChunk(new VP8XChunk(this));
    }

    if (this->chunks[WEBP_CHUNK_XMP].size() == 0) {
        XMPChunk* xmpChunk = new XMPChunk(this);
        this->addChunk(xmpChunk);
        handler->xmpChunk = xmpChunk;
        this->vp8x->xmp(true);
    }
}
