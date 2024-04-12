static EAS_BOOL QueryGUID (const DLSID *pGUID, EAS_U32 *pValue)
{

 /* assume false */
 *pValue = 0;
 if (EAS_HWMemCmp(&DLSID_GMInHardware, pGUID, sizeof(DLSID)) == 0)
 {
 *pValue = 0xffffffff;
 return EAS_TRUE;
 }

 if (EAS_HWMemCmp(&DLSID_GSInHardware, pGUID, sizeof(DLSID)) == 0)
 return EAS_TRUE;

 if (EAS_HWMemCmp(&DLSID_XGInHardware, pGUID, sizeof(DLSID)) == 0)
 return EAS_TRUE;

 if (EAS_HWMemCmp(&DLSID_SupportsDLS1, pGUID, sizeof(DLSID)) == 0)
 {
 *pValue = 0xffffffff;
 return EAS_TRUE;
 }

 if (EAS_HWMemCmp(&DLSID_SupportsDLS2, pGUID, sizeof(DLSID)) == 0)
 return EAS_TRUE;

 if (EAS_HWMemCmp(&DLSID_SampleMemorySize, pGUID, sizeof(DLSID)) == 0)
 {
 *pValue = MAX_DLS_MEMORY;
 return EAS_TRUE;
 }

 if (EAS_HWMemCmp(&DLSID_ManufacturersID, pGUID, sizeof(DLSID)) == 0)
 {
 *pValue = 0x0000013A;
 return EAS_TRUE;
 }

 if (EAS_HWMemCmp(&DLSID_ProductID, pGUID, sizeof(DLSID)) == 0)
 {
 *pValue = LIB_VERSION;
 return EAS_TRUE;
 }

 if (EAS_HWMemCmp(&DLSID_SamplePlaybackRate, pGUID, sizeof(DLSID)) == 0)
 {
 *pValue = (EAS_U32) outputSampleRate;
 return EAS_TRUE;
 }

 /* unrecognized DLSID */
 return EAS_FALSE;
}
