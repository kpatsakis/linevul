GF_Err dvcC_Size(GF_Box *s)
{
	GF_DOVIConfigurationBox *ptr = (GF_DOVIConfigurationBox *)s;

	ptr->size += sizeof(GF_DOVIDecoderConfigurationRecord);

	return GF_OK;
}
