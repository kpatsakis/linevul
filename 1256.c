int aacDecoder_drcEpilog (
        HANDLE_AAC_DRC  self,
        HANDLE_FDK_BITSTREAM hBs,
 CAacDecoderStaticChannelInfo *pAacDecoderStaticChannelInfo[],
        UCHAR  pceInstanceTag,
        UCHAR  channelMapping[], /* Channel mapping translating drcChannel index to canonical channel index */
 int    validChannels )
{
 int err = 0;

 if (self == NULL) {
 return -1;
 }

 if (self->params.bsDelayEnable)
 {
    err = aacDecoder_drcExtractAndMap (
            self,
            hBs,
            pAacDecoderStaticChannelInfo,
            pceInstanceTag,
            channelMapping,
            validChannels );
 }

 return err;
}
