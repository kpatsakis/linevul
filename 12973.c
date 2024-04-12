FileTransfer::AddDownloadFilenameRemap(char const *source_name,char const *target_name) {
	if(!download_filename_remaps.IsEmpty()) {
		download_filename_remaps += ";";
	}
	download_filename_remaps += source_name;
	download_filename_remaps += "=";
	download_filename_remaps += target_name;
}
