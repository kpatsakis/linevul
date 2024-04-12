static EAS_RESULT Parse_rgnh (SDLS_SYNTHESIZER_DATA *pDLSData, EAS_I32 pos, S_DLS_REGION *pRgn)
{
    EAS_RESULT result;
    EAS_U16 lowKey;
    EAS_U16 highKey;
    EAS_U16 lowVel;
    EAS_U16 highVel;
    EAS_U16 optionFlags;
    EAS_U16 keyGroup;

 /* seek to start of chunk */
 if ((result = EAS_HWFileSeek(pDLSData->hwInstData, pDLSData->fileHandle, pos)) != EAS_SUCCESS)
 return result;

 /* get the key range */
 if ((result = EAS_HWGetWord(pDLSData->hwInstData, pDLSData->fileHandle, &lowKey, EAS_FALSE)) != EAS_SUCCESS)
 return result;
 if ((result = EAS_HWGetWord(pDLSData->hwInstData, pDLSData->fileHandle, &highKey, EAS_FALSE)) != EAS_SUCCESS)
 return result;

 /* check the range */
 if (lowKey > 127)
 {
 { /* dpp: EAS_ReportEx(_EAS_SEVERITY_WARNING, "DLS rgnh: Low key out of range [%u]\n", lowKey); */ }
        lowKey = 127;
 }
 if (highKey > 127)
 {
 { /* dpp: EAS_ReportEx(_EAS_SEVERITY_WARNING, "DLS rgnh: High key out of range [%u]\n", lowKey); */ }
        highKey = 127;
 }

 /* get the velocity range */
 if ((result = EAS_HWGetWord(pDLSData->hwInstData, pDLSData->fileHandle, &lowVel, EAS_FALSE)) != EAS_SUCCESS)
 return result;
 if ((result = EAS_HWGetWord(pDLSData->hwInstData, pDLSData->fileHandle, &highVel, EAS_FALSE)) != EAS_SUCCESS)
 return result;

 /* check the range */
 if (lowVel > 127)
 {
 { /* dpp: EAS_ReportEx(_EAS_SEVERITY_WARNING, "DLS rgnh: Low velocity out of range [%u]\n", lowVel); */ }
        lowVel = 127;
 }
 if (highVel > 127)
 {
 { /* dpp: EAS_ReportEx(_EAS_SEVERITY_WARNING, "DLS rgnh: High velocity out of range [%u]\n", highVel); */ }
        highVel = 127;
 }

 /* get the option flags */
 if ((result = EAS_HWGetWord(pDLSData->hwInstData, pDLSData->fileHandle, &optionFlags, EAS_FALSE)) != EAS_SUCCESS)
 return result;

 /* get the key group */
 if ((result = EAS_HWGetWord(pDLSData->hwInstData, pDLSData->fileHandle, &keyGroup, EAS_FALSE)) != EAS_SUCCESS)
 return result;

 /* save the key range and key group */
    pRgn->wtRegion.region.rangeLow = (EAS_U8) lowKey;
    pRgn->wtRegion.region.rangeHigh = (EAS_U8) highKey;

 /*lint -e{734} keyGroup will always be from 0-15 */
    pRgn->wtRegion.region.keyGroupAndFlags = keyGroup << 8;
    pRgn->velLow = (EAS_U8) lowVel;
    pRgn->velHigh = (EAS_U8) highVel;
 if (optionFlags & F_RGN_OPTION_SELFNONEXCLUSIVE)
        pRgn->wtRegion.region.keyGroupAndFlags |= REGION_FLAG_NON_SELF_EXCLUSIVE;

 return EAS_SUCCESS;
}
