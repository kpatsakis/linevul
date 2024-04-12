static int udf_load_pvoldesc(struct super_block *sb, sector_t block)
{
	struct primaryVolDesc *pvoldesc;
	struct ustr *instr, *outstr;
	struct buffer_head *bh;
	uint16_t ident;
	int ret = 1;

	instr = kmalloc(sizeof(struct ustr), GFP_NOFS);
	if (!instr)
		return 1;

	outstr = kmalloc(sizeof(struct ustr), GFP_NOFS);
	if (!outstr)
		goto out1;

	bh = udf_read_tagged(sb, block, block, &ident);
	if (!bh)
		goto out2;

	BUG_ON(ident != TAG_IDENT_PVD);

	pvoldesc = (struct primaryVolDesc *)bh->b_data;

	if (udf_disk_stamp_to_time(&UDF_SB(sb)->s_record_time,
			      pvoldesc->recordingDateAndTime)) {
#ifdef UDFFS_DEBUG
		struct timestamp *ts = &pvoldesc->recordingDateAndTime;
		udf_debug("recording time %04u/%02u/%02u %02u:%02u (%x)\n",
			  le16_to_cpu(ts->year), ts->month, ts->day, ts->hour,
			  ts->minute, le16_to_cpu(ts->typeAndTimezone));
#endif
	}

	if (!udf_build_ustr(instr, pvoldesc->volIdent, 32))
		if (udf_CS0toUTF8(outstr, instr)) {
			strncpy(UDF_SB(sb)->s_volume_ident, outstr->u_name,
				outstr->u_len > 31 ? 31 : outstr->u_len);
			udf_debug("volIdent[] = '%s'\n",
				  UDF_SB(sb)->s_volume_ident);
		}

	if (!udf_build_ustr(instr, pvoldesc->volSetIdent, 128))
		if (udf_CS0toUTF8(outstr, instr))
			udf_debug("volSetIdent[] = '%s'\n", outstr->u_name);

	brelse(bh);
	ret = 0;
out2:
	kfree(outstr);
out1:
	kfree(instr);
	return ret;
}
