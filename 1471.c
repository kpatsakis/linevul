vpx_enc_frame_flags_t SoftVPXEncoder::getEncodeFlags() {
 vpx_enc_frame_flags_t flags = 0;
 int patternIdx = mTemporalPatternIdx % mTemporalPatternLength;
    mTemporalPatternIdx++;
 switch (mTemporalPattern[patternIdx]) {
 case kTemporalUpdateLast:
            flags |= VP8_EFLAG_NO_UPD_GF;
            flags |= VP8_EFLAG_NO_UPD_ARF;
            flags |= VP8_EFLAG_NO_REF_GF;
            flags |= VP8_EFLAG_NO_REF_ARF;
 break;
 case kTemporalUpdateGoldenWithoutDependency:
            flags |= VP8_EFLAG_NO_REF_GF;
 case kTemporalUpdateGolden:
            flags |= VP8_EFLAG_NO_REF_ARF;
            flags |= VP8_EFLAG_NO_UPD_ARF;
            flags |= VP8_EFLAG_NO_UPD_LAST;
 break;
 case kTemporalUpdateAltrefWithoutDependency:
            flags |= VP8_EFLAG_NO_REF_ARF;
            flags |= VP8_EFLAG_NO_REF_GF;
 case kTemporalUpdateAltref:
            flags |= VP8_EFLAG_NO_UPD_GF;
            flags |= VP8_EFLAG_NO_UPD_LAST;
 break;
 case kTemporalUpdateNoneNoRefAltref:
            flags |= VP8_EFLAG_NO_REF_ARF;
 case kTemporalUpdateNone:
            flags |= VP8_EFLAG_NO_UPD_GF;
            flags |= VP8_EFLAG_NO_UPD_ARF;
            flags |= VP8_EFLAG_NO_UPD_LAST;
            flags |= VP8_EFLAG_NO_UPD_ENTROPY;
 break;
 case kTemporalUpdateNoneNoRefGoldenRefAltRef:
            flags |= VP8_EFLAG_NO_REF_GF;
            flags |= VP8_EFLAG_NO_UPD_GF;
            flags |= VP8_EFLAG_NO_UPD_ARF;
            flags |= VP8_EFLAG_NO_UPD_LAST;
            flags |= VP8_EFLAG_NO_UPD_ENTROPY;
 break;
 case kTemporalUpdateGoldenWithoutDependencyRefAltRef:
            flags |= VP8_EFLAG_NO_REF_GF;
            flags |= VP8_EFLAG_NO_UPD_ARF;
            flags |= VP8_EFLAG_NO_UPD_LAST;
 break;
 case kTemporalUpdateLastRefAltRef:
            flags |= VP8_EFLAG_NO_UPD_GF;
            flags |= VP8_EFLAG_NO_UPD_ARF;
            flags |= VP8_EFLAG_NO_REF_GF;
 break;
 case kTemporalUpdateGoldenRefAltRef:
            flags |= VP8_EFLAG_NO_UPD_ARF;
            flags |= VP8_EFLAG_NO_UPD_LAST;
 break;
 case kTemporalUpdateLastAndGoldenRefAltRef:
            flags |= VP8_EFLAG_NO_UPD_ARF;
            flags |= VP8_EFLAG_NO_REF_GF;
 break;
 case kTemporalUpdateLastRefAll:
            flags |= VP8_EFLAG_NO_UPD_ARF;
            flags |= VP8_EFLAG_NO_UPD_GF;
 break;
 }
 return flags;
}
