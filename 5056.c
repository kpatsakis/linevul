int32_t EqualizerGetBandFreqRange(EffectContext *pContext __unused, int32_t band, uint32_t *pLow,
 uint32_t *pHi){
 *pLow = bandFreqRange[band][0];
 *pHi  = bandFreqRange[band][1];
 return 0;
}
