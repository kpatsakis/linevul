FLACParser::~FLACParser()
{
    ALOGV("FLACParser::~FLACParser");
 if (mDecoder != NULL) {
        FLAC__stream_decoder_delete(mDecoder);
        mDecoder = NULL;
 }
}
