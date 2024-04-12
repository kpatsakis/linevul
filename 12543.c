static bool check_bytes(const ut8 *buf, ut64 length) {
	return buf && length > 4 && memcmp (buf, ELFMAG, SELFMAG) == 0
		&& buf[4] != 2;
}
