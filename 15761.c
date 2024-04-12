static EAS_RESULT Parse_fmt (SDLS_SYNTHESIZER_DATA *pDLSData, EAS_I32 pos, S_WSMP_DATA *p)
{
    EAS_RESULT result;
    EAS_U16 wtemp;
    EAS_U32 ltemp;

 /* seek to start of chunk */
 if ((result = EAS_HWFileSeek(pDLSData->hwInstData, pDLSData->fileHandle, pos)) != EAS_SUCCESS)
 return result;

 /* get format tag */
 if ((result = EAS_HWGetWord(pDLSData->hwInstData, pDLSData->fileHandle, &wtemp, EAS_FALSE)) != EAS_SUCCESS)
 return result;
 if (wtemp != WAVE_FORMAT_PCM)
 {
 { /* dpp: EAS_ReportEx(_EAS_SEVERITY_ERROR, "Unsupported DLS sample format %04x\n", wtemp); */ }
 return EAS_ERROR_UNRECOGNIZED_FORMAT;
 }

 /* get number of channels */
 if ((result = EAS_HWGetWord(pDLSData->hwInstData, pDLSData->fileHandle, &wtemp, EAS_FALSE)) != EAS_SUCCESS)
 return result;
 if (wtemp != 1)
 {
 { /* dpp: EAS_ReportEx(_EAS_SEVERITY_ERROR, "No support for DLS multi-channel samples\n"); */ }
 return EAS_ERROR_UNRECOGNIZED_FORMAT;
 }

 /* get sample rate */
 if ((result = EAS_HWGetDWord(pDLSData->hwInstData, pDLSData->fileHandle, &p->sampleRate, EAS_FALSE)) != EAS_SUCCESS)
 return result;

 /* bytes/sec */
 if ((result = EAS_HWGetDWord(pDLSData->hwInstData, pDLSData->fileHandle, &ltemp, EAS_FALSE)) != EAS_SUCCESS)
 return result;

 /* block align */
 if ((result = EAS_HWGetWord(pDLSData->hwInstData, pDLSData->fileHandle, &wtemp, EAS_FALSE)) != EAS_SUCCESS)
 return result;

 /* bits/sample */
 if ((result = EAS_HWGetWord(pDLSData->hwInstData, pDLSData->fileHandle, &p->bitsPerSample, EAS_FALSE)) != EAS_SUCCESS)
 return result;

 if ((p->bitsPerSample != 8) && (p->bitsPerSample != 16))
 {
 { /* dpp: EAS_ReportEx(_EAS_SEVERITY_ERROR, "Unsupported DLS bits-per-sample %d\n", p->bitsPerSample); */ }
 return EAS_ERROR_UNRECOGNIZED_FORMAT;
 }

 return EAS_SUCCESS;
}
