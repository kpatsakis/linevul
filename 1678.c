int LvmBundle_process(LVM_INT16        *pIn,
                      LVM_INT16        *pOut,
 int              frameCount,
 EffectContext *pContext){

 LVM_ControlParams_t ActiveParams; /* Current control Parameters */
    LVM_ReturnStatus_en     LvmStatus = LVM_SUCCESS; /* Function call status */
    LVM_INT16               *pOutTmp;

 if (pContext->config.outputCfg.accessMode == EFFECT_BUFFER_ACCESS_WRITE){
        pOutTmp = pOut;
 }else if (pContext->config.outputCfg.accessMode == EFFECT_BUFFER_ACCESS_ACCUMULATE){
 if (pContext->pBundledContext->frameCount != frameCount) {
 if (pContext->pBundledContext->workBuffer != NULL) {
                free(pContext->pBundledContext->workBuffer);
 }
            pContext->pBundledContext->workBuffer =
 (LVM_INT16 *)malloc(frameCount * sizeof(LVM_INT16) * 2);
            pContext->pBundledContext->frameCount = frameCount;
 }
        pOutTmp = pContext->pBundledContext->workBuffer;
 }else{
        ALOGV("LVM_ERROR : LvmBundle_process invalid access mode");
 return -EINVAL;
 }

 #ifdef LVM_PCM
    fwrite(pIn, frameCount*sizeof(LVM_INT16)*2, 1, pContext->pBundledContext->PcmInPtr);
    fflush(pContext->pBundledContext->PcmInPtr);
 #endif


 /* Process the samples */
 LvmStatus = LVM_Process(pContext->pBundledContext->hInstance, /* Instance handle */
                            pIn, /* Input buffer */
                            pOutTmp, /* Output buffer */
 (LVM_UINT16)frameCount, /* Number of samples to read */
 0); /* Audo Time */

    LVM_ERROR_CHECK(LvmStatus, "LVM_Process", "LvmBundle_process")
 if(LvmStatus != LVM_SUCCESS) return -EINVAL;

 #ifdef LVM_PCM
    fwrite(pOutTmp, frameCount*sizeof(LVM_INT16)*2, 1, pContext->pBundledContext->PcmOutPtr);
    fflush(pContext->pBundledContext->PcmOutPtr);
 #endif

 if (pContext->config.outputCfg.accessMode == EFFECT_BUFFER_ACCESS_ACCUMULATE){
 for (int i=0; i<frameCount*2; i++){
            pOut[i] = clamp16((LVM_INT32)pOut[i] + (LVM_INT32)pOutTmp[i]);
 }
 }
 return 0;
} /* end LvmBundle_process */
