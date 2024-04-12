GF_Err hvcc_Read(GF_Box *s, GF_BitStream *bs)
{
	u64 pos;
	GF_HEVCConfigurationBox *ptr = (GF_HEVCConfigurationBox *)s;

	if (ptr->config) gf_odf_hevc_cfg_del(ptr->config);

	pos = gf_bs_get_position(bs);
	ptr->config = gf_odf_hevc_cfg_read_bs(bs, (s->type == GF_ISOM_BOX_TYPE_HVCC) ? GF_FALSE : GF_TRUE);
	pos = gf_bs_get_position(bs) - pos ;
	if (pos < ptr->size)
		ptr->size -= (u32) pos;

	return ptr->config ? GF_OK : GF_ISOM_INVALID_FILE;
}
