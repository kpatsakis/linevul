int read_fs_bytes(int fd, long long byte, int bytes, void *buff)
{
	off_t off = byte;
	int res, count;

	TRACE("read_bytes: reading from position 0x%llx, bytes %d\n", byte,
		bytes);

	if(lseek(fd, off + squashfs_start_offset, SEEK_SET) == -1) {
		ERROR("Lseek failed because %s\n", strerror(errno));
		return FALSE;
	}

	for(count = 0; count < bytes; count += res) {
		res = read(fd, buff + count, bytes - count);
		if(res < 1) {
			if(res == 0) {
				ERROR("Read on filesystem failed because "
					"EOF\n");
				return FALSE;
			} else if(errno != EINTR) {
				ERROR("Read on filesystem failed because %s\n",
						strerror(errno));
				return FALSE;
			} else
				res = 0;
		}
	}

	return TRUE;
}
