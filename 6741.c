static EAS_RESULT Parse_ins (SDLS_SYNTHESIZER_DATA *pDLSData, EAS_I32 pos, EAS_I32 size)
{
    EAS_RESULT result;
    EAS_U32 temp;
    EAS_I32 chunkPos;
    EAS_I32 endChunk;
    EAS_I32 lrgnPos;
    EAS_I32 lrgnSize;
    EAS_I32 lartPos;
    EAS_I32 lartSize;
    EAS_I32 lar2Pos;
    EAS_I32 lar2Size;
    EAS_I32 inshPos;
    EAS_U32 regionCount;
    EAS_U32 locale;
    S_DLS_ART_VALUES art;
    S_PROGRAM *pProgram;
    EAS_U16 artIndex;

 /* seek to start of chunk */
 if ((result = EAS_HWFileSeek(pDLSData->hwInstData, pDLSData->fileHandle, pos)) != EAS_SUCCESS)
 return result;

 /* no chunks yet */
    lrgnPos = lrgnSize = lartPos = lartSize = lar2Pos = lar2Size = inshPos = artIndex = 0;

 /* read to end of chunk */
    endChunk = pos + size;
 while (pos < endChunk)
 {
        chunkPos = pos;

 /* get the next chunk type */
 if ((result = NextChunk(pDLSData, &pos, &temp, &size)) != EAS_SUCCESS)
 return result;

 /* parse useful chunks */
 switch (temp)
 {
 case CHUNK_INSH:
                inshPos = chunkPos + 8;
 break;

 case CHUNK_LART:
                lartPos = chunkPos + 12;
                lartSize = size;
 break;

 case CHUNK_LAR2:
                lar2Pos = chunkPos + 12;
                lar2Size = size;
 break;

 case CHUNK_LRGN:
                lrgnPos = chunkPos + 12;
                lrgnSize = size;
 break;

 default:
 break;
 }
 }

 /* must have an lrgn to be useful */
 if (!lrgnPos)
 {
 { /* dpp: EAS_ReportEx(_EAS_SEVERITY_ERROR, "DLS ins chunk has no lrgn chunk\n"); */ }
 return EAS_ERROR_UNRECOGNIZED_FORMAT;
 }

 /* must have an insh to be useful */
 if (!inshPos)
 {
 { /* dpp: EAS_ReportEx(_EAS_SEVERITY_ERROR, "DLS ins chunk has no insh chunk\n"); */ }
 return EAS_ERROR_UNRECOGNIZED_FORMAT;
 }

 /* parse the instrument header */
 if ((result = Parse_insh(pDLSData, inshPos, &regionCount, &locale)) != EAS_SUCCESS)
 return result;

 /* initialize and parse the global data first */
    EAS_HWMemCpy(&art, &defaultArt, sizeof(S_DLS_ART_VALUES));
 if (lartPos)
 if ((result = Parse_lart(pDLSData, lartPos, lartSize, &art)) != EAS_SUCCESS)
 return result;
 if (lar2Pos)
 if ((result = Parse_lart(pDLSData, lar2Pos, lar2Size, &art)) != EAS_SUCCESS)
 return result;

 if (art.values[PARAM_MODIFIED])
 {
        artIndex = (EAS_U16) pDLSData->artCount;
        pDLSData->artCount++;
 }

 /* convert data on second pass */
 if (pDLSData->pDLS)
 {

 if (art.values[PARAM_MODIFIED])
 Convert_art(pDLSData, &art, artIndex);

 /* setup pointers */
        pProgram = &pDLSData->pDLS->pDLSPrograms[pDLSData->instCount];

 /* initialize instrument */
        pProgram->locale = locale;
        pProgram->regionIndex = (EAS_U16) pDLSData->regionCount | FLAG_RGN_IDX_DLS_SYNTH;

 }

 /* parse the region data */
 if ((result = Parse_lrgn(pDLSData, lrgnPos, lrgnSize, artIndex, regionCount)) != EAS_SUCCESS)
 return result;

 /* bump instrument count */
    pDLSData->instCount++;
 return EAS_SUCCESS;
}
