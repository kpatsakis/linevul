static EAS_RESULT Parse_art (SDLS_SYNTHESIZER_DATA *pDLSData, EAS_I32 pos, S_DLS_ART_VALUES *pArt)
{
    EAS_RESULT result;
    EAS_U32 structSize;
    EAS_U32 numConnections;
    EAS_U16 source;
    EAS_U16 control;
    EAS_U16 destination;
    EAS_U16 transform;
    EAS_I32 scale;
    EAS_INT i;

 /* seek to start of data */
 if ((result = EAS_HWFileSeek(pDLSData->hwInstData, pDLSData->fileHandle, pos)) != EAS_SUCCESS)
 return result;

 /* get the structure size */
 if ((result = EAS_HWGetDWord(pDLSData->hwInstData, pDLSData->fileHandle, &structSize, EAS_FALSE)) != EAS_SUCCESS)
 return result;
    pos += (EAS_I32) structSize;

 /* get the number of connections */
 if ((result = EAS_HWGetDWord(pDLSData->hwInstData, pDLSData->fileHandle, &numConnections, EAS_FALSE)) != EAS_SUCCESS)
 return result;

 /* skip to start of connections */
 if ((result = EAS_HWFileSeek(pDLSData->hwInstData, pDLSData->fileHandle, pos)) != EAS_SUCCESS)
 return result;

 while (numConnections--)
 {

 /* read the connection data */
 if ((result = EAS_HWGetWord(pDLSData->hwInstData, pDLSData->fileHandle, &source, EAS_FALSE)) != EAS_SUCCESS)
 return result;
 if ((result = EAS_HWGetWord(pDLSData->hwInstData, pDLSData->fileHandle, &control, EAS_FALSE)) != EAS_SUCCESS)
 return result;
 if ((result = EAS_HWGetWord(pDLSData->hwInstData, pDLSData->fileHandle, &destination, EAS_FALSE)) != EAS_SUCCESS)
 return result;
 if ((result = EAS_HWGetWord(pDLSData->hwInstData, pDLSData->fileHandle, &transform, EAS_FALSE)) != EAS_SUCCESS)
 return result;
 if ((result = EAS_HWGetDWord(pDLSData->hwInstData, pDLSData->fileHandle, &scale, EAS_FALSE)) != EAS_SUCCESS)
 return result;

 /* look up the connection */
 for (i = 0; i < (EAS_INT) ENTRIES_IN_CONN_TABLE; i++)
 {
 if ((connTable[i].source == source) &&
 (connTable[i].destination == destination) &&
 (connTable[i].control == control))
 {
 /*lint -e{704} use shift for performance */
                pArt->values[connTable[i].connection] = (EAS_I16) (scale >> 16);
                pArt->values[PARAM_MODIFIED] = EAS_TRUE;
 break;
 }
 }
 if (i == PARAM_TABLE_SIZE)
 { /* dpp: EAS_ReportEx(_EAS_SEVERITY_WARNING, "WARN: Unsupported parameter in DLS file\n"); */ }
 }

 return EAS_SUCCESS;
}
