int FS_FOpenFileRead_Filtered( const char *qpath, fileHandle_t *file, qboolean uniqueFILE, int filter_flag ) {
	int ret;

	fs_filter_flag = filter_flag;
	ret = FS_FOpenFileRead( qpath, file, uniqueFILE );
	fs_filter_flag = 0;

	return ret;
}
