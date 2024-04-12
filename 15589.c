SecHandle* sspi_SecureHandleAlloc()
{
	SecHandle* handle = (SecHandle*) malloc(sizeof(SecHandle));
	sspi_SecureHandleInit(handle);
	return handle;
}
