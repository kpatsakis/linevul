qboolean FS_CompareZipChecksum(const char *zipfile)
{
	pack_t *thepak;
	int index, checksum;
	
	thepak = FS_LoadZipFile(zipfile, "");
	
	if(!thepak)
		return qfalse;
	
	checksum = thepak->checksum;
	FS_FreePak(thepak);
	
	for(index = 0; index < fs_numServerReferencedPaks; index++)
	{
		if(checksum == fs_serverReferencedPaks[index])
			return qtrue;
	}
	
	return qfalse;
}
