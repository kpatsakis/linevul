BOOL security_fips_encrypt(BYTE* data, int length, rdpRdp* rdp)
{
	crypto_des3_encrypt(rdp->fips_encrypt, length, data, data);
	rdp->encrypt_use_count++;
	return TRUE;
}
