UWORD32 ih264d_uev(UWORD32 *pu4_bitstrm_ofst, UWORD32 *pu4_bitstrm_buf)
{
    UWORD32 u4_bitstream_offset = *pu4_bitstrm_ofst;
    UWORD32 u4_word, u4_ldz;

 /***************************************************************/
 /* Find leading zeros in next 32 bits                          */
 /***************************************************************/
    NEXTBITS_32(u4_word, u4_bitstream_offset, pu4_bitstrm_buf);
    u4_ldz = CLZ(u4_word);
 /* Flush the ps_bitstrm */
    u4_bitstream_offset += (u4_ldz + 1);
 /* Read the suffix from the ps_bitstrm */
    u4_word = 0;
 if(u4_ldz)
        GETBITS(u4_word, u4_bitstream_offset, pu4_bitstrm_buf, u4_ldz);
 *pu4_bitstrm_ofst = u4_bitstream_offset;
 return ((1 << u4_ldz) + u4_word - 1);
}
