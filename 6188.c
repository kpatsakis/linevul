void	FS_Flush( fileHandle_t f ) {
	fflush(fsh[f].handleFiles.file.o);
}
