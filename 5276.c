static void iwjpeg_read_saved_markers(struct iwjpegrcontext *rctx,
	struct jpeg_decompress_struct *cinfo)
{
	struct jpeg_marker_struct *mk;
	const iw_byte *d;

	mk = cinfo->marker_list;

	while(mk) {
		d = (const iw_byte*)mk->data;

		if(mk->marker==0xe1) {
			if(mk->data_length>=6 && d[0]=='E' && d[1]=='x' &&
				d[2]=='i' && d[3]=='f' && d[4]==0)
			{
				iwjpeg_scan_exif(rctx, &d[6], mk->data_length-6);
			}
		}

		mk = mk->next;
	}
}
