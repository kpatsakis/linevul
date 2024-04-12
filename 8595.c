mode_list(struct cpio *cpio)
{
	struct archive *a;
	struct archive_entry *entry;
	int r;

	a = archive_read_new();
	if (a == NULL)
		lafe_errc(1, 0, "Couldn't allocate archive object");
	archive_read_support_filter_all(a);
	archive_read_support_format_all(a);
	if (cpio->passphrase != NULL)
		r = archive_read_add_passphrase(a, cpio->passphrase);
	else
		r = archive_read_set_passphrase_callback(a, cpio,
			&passphrase_callback);
	if (r != ARCHIVE_OK)
		lafe_errc(1, 0, "%s", archive_error_string(a));

	if (archive_read_open_filename(a, cpio->filename,
					cpio->bytes_per_block))
		lafe_errc(1, archive_errno(a),
		    "%s", archive_error_string(a));
	for (;;) {
		r = archive_read_next_header(a, &entry);
		if (r == ARCHIVE_EOF)
			break;
		if (r != ARCHIVE_OK) {
			lafe_errc(1, archive_errno(a),
			    "%s", archive_error_string(a));
		}
		if (archive_match_path_excluded(cpio->matching, entry))
			continue;
		if (cpio->verbose)
			list_item_verbose(cpio, entry);
		else
			fprintf(stdout, "%s\n", archive_entry_pathname(entry));
	}
	r = archive_read_close(a);
	if (r != ARCHIVE_OK)
		lafe_errc(1, 0, "%s", archive_error_string(a));
	if (!cpio->quiet) {
		int64_t blocks = (archive_filter_bytes(a, 0) + 511)
			      / 512;
		fprintf(stderr, "%lu %s\n", (unsigned long)blocks,
		    blocks == 1 ? "block" : "blocks");
	}
	archive_read_free(a);
	exit(0);
}
