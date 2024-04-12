void ihevcd_copy_slice_hdr(codec_t *ps_codec, WORD32 slice_idx, WORD32 slice_idx_ref)
{
 slice_header_t *ps_slice_hdr, *ps_slice_hdr_ref;
    WORD32 *pu4_entry_offset_backup;

    ps_slice_hdr = ps_codec->s_parse.ps_slice_hdr_base + slice_idx;
    ps_slice_hdr_ref = ps_codec->s_parse.ps_slice_hdr_base + slice_idx_ref;

    pu4_entry_offset_backup = ps_slice_hdr->pu4_entry_point_offset;
    memcpy(ps_slice_hdr, ps_slice_hdr_ref, sizeof(slice_header_t));
    ps_slice_hdr->pu4_entry_point_offset = pu4_entry_offset_backup;
}
