int Reverb_init(ReverbContext *pContext){
 int status;

    ALOGV("\tReverb_init start");

    CHECK_ARG(pContext != NULL);

 if (pContext->hInstance != NULL){
 Reverb_free(pContext);
 }

    pContext->config.inputCfg.accessMode                    = EFFECT_BUFFER_ACCESS_READ;
 if (pContext->auxiliary) {
        pContext->config.inputCfg.channels                  = AUDIO_CHANNEL_OUT_MONO;
 } else {
        pContext->config.inputCfg.channels                  = AUDIO_CHANNEL_OUT_STEREO;
 }

    pContext->config.inputCfg.format                        = AUDIO_FORMAT_PCM_16_BIT;
    pContext->config.inputCfg.samplingRate                  = 44100;
    pContext->config.inputCfg.bufferProvider.getBuffer      = NULL;
    pContext->config.inputCfg.bufferProvider.releaseBuffer  = NULL;
    pContext->config.inputCfg.bufferProvider.cookie         = NULL;
    pContext->config.inputCfg.mask                          = EFFECT_CONFIG_ALL;
    pContext->config.outputCfg.accessMode                   = EFFECT_BUFFER_ACCESS_ACCUMULATE;
    pContext->config.outputCfg.channels                     = AUDIO_CHANNEL_OUT_STEREO;
    pContext->config.outputCfg.format                       = AUDIO_FORMAT_PCM_16_BIT;
    pContext->config.outputCfg.samplingRate                 = 44100;
    pContext->config.outputCfg.bufferProvider.getBuffer     = NULL;
    pContext->config.outputCfg.bufferProvider.releaseBuffer = NULL;
    pContext->config.outputCfg.bufferProvider.cookie        = NULL;
    pContext->config.outputCfg.mask                         = EFFECT_CONFIG_ALL;

    pContext->leftVolume = REVERB_UNIT_VOLUME;
    pContext->rightVolume = REVERB_UNIT_VOLUME;
    pContext->prevLeftVolume = REVERB_UNIT_VOLUME;
    pContext->prevRightVolume = REVERB_UNIT_VOLUME;
    pContext->volumeMode = REVERB_VOLUME_FLAT;

    LVREV_ReturnStatus_en     LvmStatus=LVREV_SUCCESS; /* Function call status */
    LVREV_ControlParams_st    params; /* Control Parameters */
    LVREV_InstanceParams_st   InstParams; /* Instance parameters */
    LVREV_MemoryTable_st      MemTab; /* Memory allocation table */
 bool                      bMallocFailure = LVM_FALSE;

 /* Set the capabilities */
 InstParams.MaxBlockSize = MAX_CALL_SIZE;
 InstParams.SourceFormat = LVM_STEREO; // Max format, could be mono during process
 InstParams.NumDelays = LVREV_DELAYLINES_4;

 /* Allocate memory, forcing alignment */
 LvmStatus = LVREV_GetMemoryTable(LVM_NULL,
 &MemTab,
 &InstParams);

    LVM_ERROR_CHECK(LvmStatus, "LVREV_GetMemoryTable", "Reverb_init")
 if(LvmStatus != LVREV_SUCCESS) return -EINVAL;

    ALOGV("\tCreateInstance Succesfully called LVM_GetMemoryTable\n");

 /* Allocate memory */
 for (int i=0; i<LVM_NR_MEMORY_REGIONS; i++){
 if (MemTab.Region[i].Size != 0){
 MemTab.Region[i].pBaseAddress = malloc(MemTab.Region[i].Size);

 if (MemTab.Region[i].pBaseAddress == LVM_NULL){
                ALOGV("\tLVREV_ERROR :Reverb_init CreateInstance Failed to allocate %" PRIu32
 " bytes for region %u\n", MemTab.Region[i].Size, i );
                bMallocFailure = LVM_TRUE;
 }else{
                ALOGV("\tReverb_init CreateInstance allocate %" PRIu32
 " bytes for region %u at %p\n",
 MemTab.Region[i].Size, i, MemTab.Region[i].pBaseAddress);
 }
 }
 }

 /* If one or more of the memory regions failed to allocate, free the regions that were
     * succesfully allocated and return with an error
     */
 if(bMallocFailure == LVM_TRUE){
 for (int i=0; i<LVM_NR_MEMORY_REGIONS; i++){
 if (MemTab.Region[i].pBaseAddress == LVM_NULL){
                ALOGV("\tLVM_ERROR :Reverb_init CreateInstance Failed to allocate %" PRIu32
 " bytes for region %u - Not freeing\n", MemTab.Region[i].Size, i );
 }else{
                ALOGV("\tLVM_ERROR :Reverb_init CreateInstance Failed: but allocated %" PRIu32
 " bytes for region %u at %p- free\n",
 MemTab.Region[i].Size, i, MemTab.Region[i].pBaseAddress);
                free(MemTab.Region[i].pBaseAddress);
 }
 }
 return -EINVAL;
 }
    ALOGV("\tReverb_init CreateInstance Succesfully malloc'd memory\n");

 /* Initialise */
    pContext->hInstance = LVM_NULL;

 /* Init sets the instance handle */
 LvmStatus = LVREV_GetInstanceHandle(&pContext->hInstance,
 &MemTab,
 &InstParams);

    LVM_ERROR_CHECK(LvmStatus, "LVM_GetInstanceHandle", "Reverb_init")
 if(LvmStatus != LVREV_SUCCESS) return -EINVAL;

    ALOGV("\tReverb_init CreateInstance Succesfully called LVM_GetInstanceHandle\n");

 /* Set the initial process parameters */
 /* General parameters */
    params.OperatingMode = LVM_MODE_ON;
    params.SampleRate = LVM_FS_44100;
    pContext->SampleRate = LVM_FS_44100;

 if(pContext->config.inputCfg.channels == AUDIO_CHANNEL_OUT_MONO){
        params.SourceFormat = LVM_MONO;
 } else {
        params.SourceFormat = LVM_STEREO;
 }

 /* Reverb parameters */
    params.Level = 0;
    params.LPF            = 23999;
    params.HPF            = 50;
    params.T60            = 1490;
    params.Density = 100;
    params.Damping = 21;
    params.RoomSize = 100;

    pContext->SamplesToExitCount = (params.T60 * pContext->config.inputCfg.samplingRate)/1000;

 /* Saved strength is used to return the exact strength that was used in the set to the get
     * because we map the original strength range of 0:1000 to 1:15, and this will avoid
     * quantisation like effect when returning
     */
    pContext->SavedRoomLevel = -6000;
    pContext->SavedHfLevel = 0;
    pContext->bEnabled          = LVM_FALSE;
    pContext->SavedDecayTime = params.T60;
    pContext->SavedDecayHfRatio = params.Damping*20;
    pContext->SavedDensity = params.RoomSize*10;
    pContext->SavedDiffusion = params.Density*10;
    pContext->SavedReverbLevel = -6000;

 /* Activate the initial settings */
 LvmStatus = LVREV_SetControlParameters(pContext->hInstance,
 &params);

    LVM_ERROR_CHECK(LvmStatus, "LVREV_SetControlParameters", "Reverb_init")
 if(LvmStatus != LVREV_SUCCESS) return -EINVAL;

    ALOGV("\tReverb_init CreateInstance Succesfully called LVREV_SetControlParameters\n");
    ALOGV("\tReverb_init End");
 return 0;
} /* end Reverb_init */
