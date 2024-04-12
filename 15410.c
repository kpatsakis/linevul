cleanup_volume_info(struct smb_vol **pvolume_info)
{
	struct smb_vol *volume_info;

	if (!pvolume_info || !*pvolume_info)
		return;

	volume_info = *pvolume_info;
	kzfree(volume_info->password);
	kfree(volume_info->UNC);
	kfree(volume_info->prepath);
	kfree(volume_info);
	*pvolume_info = NULL;
	return;
}
