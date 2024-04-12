static void  Free_PosClassRule( HB_PosClassRule*  pcr )
{
  FREE( pcr->PosLookupRecord );
  FREE( pcr->Class );
}
