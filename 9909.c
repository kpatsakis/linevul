int VolumeSetVolumeLevel(EffectContext *pContext, int16_t level){

 if (level > 0 || level < -9600) {
 return -EINVAL;
 }

 if (pContext->pBundledContext->bMuteEnabled == LVM_TRUE) {
        pContext->pBundledContext->levelSaved = level / 100;
 } else {
        pContext->pBundledContext->volume = level / 100;
 }

 LvmEffect_limitLevel(pContext);

 return 0;
} /* end VolumeSetVolumeLevel */
