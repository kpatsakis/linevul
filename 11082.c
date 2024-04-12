int LvmBundle_init(EffectContext *pContext){
 int status;

    ALOGV("\tLvmBundle_init start");

    pContext->config.inputCfg.accessMode                    = EFFECT_BUFFER_ACCESS_READ;
    pContext->config.inputCfg.channels                      = AUDIO_CHANNEL_OUT_STEREO;
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

    CHECK_ARG(pContext != NULL);

 if (pContext->pBundledContext->hInstance != NULL){
        ALOGV("\tLvmBundle_init pContext->pBassBoost != NULL "
 "-> Calling pContext->pBassBoost->free()");

 LvmEffect_free(pContext);

        ALOGV("\tLvmBundle_init pContext->pBassBoost != NULL "
 "-> Called pContext->pBassBoost->free()");
 }

    LVM_ReturnStatus_en     LvmStatus=LVM_SUCCESS; /* Function call status */
 LVM_ControlParams_t     params; /* Control Parameters */
 LVM_InstParams_t InstParams; /* Instance parameters */
 LVM_EQNB_BandDef_t BandDefs[MAX_NUM_BANDS]; /* Equaliser band definitions */
 LVM_HeadroomParams_t HeadroomParams; /* Headroom parameters */
 LVM_HeadroomBandDef_t HeadroomBandDef[LVM_HEADROOM_MAX_NBANDS];
 LVM_MemTab_t MemTab; /* Memory allocation table */
 bool                    bMallocFailure = LVM_FALSE;

 /* Set the capabilities */
 InstParams.BufferMode = LVM_UNMANAGED_BUFFERS;
 InstParams.MaxBlockSize = MAX_CALL_SIZE;
 InstParams.EQNB_NumBands    = MAX_NUM_BANDS;
 InstParams.PSA_Included     = LVM_PSA_ON;

 /* Allocate memory, forcing alignment */
 LvmStatus = LVM_GetMemoryTable(LVM_NULL,
 &MemTab,
 &InstParams);

    LVM_ERROR_CHECK(LvmStatus, "LVM_GetMemoryTable", "LvmBundle_init")
 if(LvmStatus != LVM_SUCCESS) return -EINVAL;

    ALOGV("\tCreateInstance Succesfully called LVM_GetMemoryTable\n");

 /* Allocate memory */
 for (int i=0; i<LVM_NR_MEMORY_REGIONS; i++){
 if (MemTab.Region[i].Size != 0){
 MemTab.Region[i].pBaseAddress = malloc(MemTab.Region[i].Size);

 if (MemTab.Region[i].pBaseAddress == LVM_NULL){
                ALOGV("\tLVM_ERROR :LvmBundle_init CreateInstance Failed to allocate %ld bytes "
 "for region %u\n", MemTab.Region[i].Size, i );
                bMallocFailure = LVM_TRUE;
 }else{
                ALOGV("\tLvmBundle_init CreateInstance allocated %ld bytes for region %u at %p\n",
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
                ALOGV("\tLVM_ERROR :LvmBundle_init CreateInstance Failed to allocate %ld bytes "
 "for region %u Not freeing\n", MemTab.Region[i].Size, i );
 }else{
                ALOGV("\tLVM_ERROR :LvmBundle_init CreateInstance Failed: but allocated %ld bytes "
 "for region %u at %p- free\n",
 MemTab.Region[i].Size, i, MemTab.Region[i].pBaseAddress);
                free(MemTab.Region[i].pBaseAddress);
 }
 }
 return -EINVAL;
 }
    ALOGV("\tLvmBundle_init CreateInstance Succesfully malloc'd memory\n");

 /* Initialise */
    pContext->pBundledContext->hInstance = LVM_NULL;

 /* Init sets the instance handle */
 LvmStatus = LVM_GetInstanceHandle(&pContext->pBundledContext->hInstance,
 &MemTab,
 &InstParams);

    LVM_ERROR_CHECK(LvmStatus, "LVM_GetInstanceHandle", "LvmBundle_init")
 if(LvmStatus != LVM_SUCCESS) return -EINVAL;

    ALOGV("\tLvmBundle_init CreateInstance Succesfully called LVM_GetInstanceHandle\n");

 /* Set the initial process parameters */
 /* General parameters */
    params.OperatingMode = LVM_MODE_ON;
    params.SampleRate = LVM_FS_44100;
    params.SourceFormat = LVM_STEREO;
    params.SpeakerType = LVM_HEADPHONES;

    pContext->pBundledContext->SampleRate = LVM_FS_44100;

 /* Concert Sound parameters */
    params.VirtualizerOperatingMode = LVM_MODE_OFF;
    params.VirtualizerType = LVM_CONCERTSOUND;
    params.VirtualizerReverbLevel = 100;
    params.CS_EffectLevel             = LVM_CS_EFFECT_NONE;

 /* N-Band Equaliser parameters */
    params.EQNB_OperatingMode     = LVM_EQNB_OFF;
    params.EQNB_NBands            = FIVEBAND_NUMBANDS;
    params.pEQNB_BandDefinition   = &BandDefs[0];

 for (int i=0; i<FIVEBAND_NUMBANDS; i++)
 {
 BandDefs[i].Frequency = EQNB_5BandPresetsFrequencies[i];
 BandDefs[i].QFactor = EQNB_5BandPresetsQFactors[i];
 BandDefs[i].Gain = EQNB_5BandSoftPresets[i];
 }

 /* Volume Control parameters */
    params.VC_EffectLevel         = 0;
    params.VC_Balance             = 0;

 /* Treble Enhancement parameters */
    params.TE_OperatingMode       = LVM_TE_OFF;
    params.TE_EffectLevel         = 0;

 /* PSA Control parameters */
    params.PSA_Enable             = LVM_PSA_OFF;
    params.PSA_PeakDecayRate      = (LVM_PSA_DecaySpeed_en)0;

 /* Bass Enhancement parameters */
    params.BE_OperatingMode       = LVM_BE_OFF;
    params.BE_EffectLevel         = 0;
    params.BE_CentreFreq          = LVM_BE_CENTRE_90Hz;
    params.BE_HPF                 = LVM_BE_HPF_ON;

 /* PSA Control parameters */
    params.PSA_Enable             = LVM_PSA_OFF;
    params.PSA_PeakDecayRate      = LVM_PSA_SPEED_MEDIUM;

 /* TE Control parameters */
    params.TE_OperatingMode       = LVM_TE_OFF;
    params.TE_EffectLevel         = 0;

 /* Activate the initial settings */
 LvmStatus = LVM_SetControlParameters(pContext->pBundledContext->hInstance,
 &params);

    LVM_ERROR_CHECK(LvmStatus, "LVM_SetControlParameters", "LvmBundle_init")
 if(LvmStatus != LVM_SUCCESS) return -EINVAL;

    ALOGV("\tLvmBundle_init CreateInstance Succesfully called LVM_SetControlParameters\n");

 /* Set the headroom parameters */
 HeadroomBandDef[0].Limit_Low = 20;
 HeadroomBandDef[0].Limit_High = 4999;
 HeadroomBandDef[0].Headroom_Offset = 0;
 HeadroomBandDef[1].Limit_Low = 5000;
 HeadroomBandDef[1].Limit_High = 24000;
 HeadroomBandDef[1].Headroom_Offset = 0;
 HeadroomParams.pHeadroomDefinition    = &HeadroomBandDef[0];
 HeadroomParams.Headroom_OperatingMode = LVM_HEADROOM_ON;
 HeadroomParams.NHeadroomBands = 2;

 LvmStatus = LVM_SetHeadroomParams(pContext->pBundledContext->hInstance,
 &HeadroomParams);

    LVM_ERROR_CHECK(LvmStatus, "LVM_SetHeadroomParams", "LvmBundle_init")
 if(LvmStatus != LVM_SUCCESS) return -EINVAL;

    ALOGV("\tLvmBundle_init CreateInstance Succesfully called LVM_SetHeadroomParams\n");
    ALOGV("\tLvmBundle_init End");
 return 0;
} /* end LvmBundle_init */
