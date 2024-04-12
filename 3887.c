void __audit_mmap_fd(int fd, int flags)
{
	struct audit_context *context = current->audit_context;
	context->mmap.fd = fd;
	context->mmap.flags = flags;
	context->type = AUDIT_MMAP;
}
