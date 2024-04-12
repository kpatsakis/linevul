int fix_log_file_owner(uid_t uid, gid_t gid)
{
	int r1 = 0, r2 = 0;

	if (!(log_fp = open_log_file()))
		return -1;
	r1 = fchown(fileno(log_fp), uid, gid);

	if (open_debug_log() != OK)
		return -1;
	if (debug_file_fp)
		r2 = fchown(fileno(debug_file_fp), uid, gid);

	/* return 0 if both are 0 and otherwise < 0 */
	return r1 < r2 ? r1 : r2;
}
