http_write(const struct http *hp, int lvl, const char *pfx)
{
	int l;

	AZ(VSB_finish(hp->vsb));
	vtc_dump(hp->vl, lvl, pfx, VSB_data(hp->vsb), VSB_len(hp->vsb));
	l = write(hp->fd, VSB_data(hp->vsb), VSB_len(hp->vsb));
	if (l != VSB_len(hp->vsb))
		vtc_log(hp->vl, hp->fatal, "Write failed: (%d vs %d) %s",
		    l, VSB_len(hp->vsb), strerror(errno));
}
