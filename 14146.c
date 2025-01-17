static int udf_load_partdesc(struct super_block *sb, sector_t block)
{
	struct buffer_head *bh;
	struct partitionDesc *p;
	struct udf_part_map *map;
	struct udf_sb_info *sbi = UDF_SB(sb);
	int i, type1_idx;
	uint16_t partitionNumber;
	uint16_t ident;
	int ret = 0;

	bh = udf_read_tagged(sb, block, block, &ident);
	if (!bh)
		return 1;
	if (ident != TAG_IDENT_PD)
		goto out_bh;

	p = (struct partitionDesc *)bh->b_data;
	partitionNumber = le16_to_cpu(p->partitionNumber);

	/* First scan for TYPE1, SPARABLE and METADATA partitions */
	for (i = 0; i < sbi->s_partitions; i++) {
		map = &sbi->s_partmaps[i];
		udf_debug("Searching map: (%d == %d)\n",
			  map->s_partition_num, partitionNumber);
		if (map->s_partition_num == partitionNumber &&
		    (map->s_partition_type == UDF_TYPE1_MAP15 ||
		     map->s_partition_type == UDF_SPARABLE_MAP15))
			break;
	}

	if (i >= sbi->s_partitions) {
		udf_debug("Partition (%d) not found in partition map\n",
			  partitionNumber);
		goto out_bh;
	}

	ret = udf_fill_partdesc_info(sb, p, i);

	/*
	 * Now rescan for VIRTUAL or METADATA partitions when SPARABLE and
	 * PHYSICAL partitions are already set up
	 */
	type1_idx = i;
	for (i = 0; i < sbi->s_partitions; i++) {
		map = &sbi->s_partmaps[i];

		if (map->s_partition_num == partitionNumber &&
		    (map->s_partition_type == UDF_VIRTUAL_MAP15 ||
		     map->s_partition_type == UDF_VIRTUAL_MAP20 ||
		     map->s_partition_type == UDF_METADATA_MAP25))
			break;
	}

	if (i >= sbi->s_partitions)
		goto out_bh;

	ret = udf_fill_partdesc_info(sb, p, i);
	if (ret)
		goto out_bh;

	if (map->s_partition_type == UDF_METADATA_MAP25) {
		ret = udf_load_metadata_files(sb, i);
		if (ret) {
			udf_err(sb, "error loading MetaData partition map %d\n",
				i);
			goto out_bh;
		}
	} else {
		ret = udf_load_vat(sb, i, type1_idx);
		if (ret)
			goto out_bh;
		/*
		 * Mark filesystem read-only if we have a partition with
		 * virtual map since we don't handle writing to it (we
		 * overwrite blocks instead of relocating them).
		 */
		sb->s_flags |= MS_RDONLY;
		pr_notice("Filesystem marked read-only because writing to pseudooverwrite partition is not implemented\n");
	}
out_bh:
	/* In case loading failed, we handle cleanup in udf_fill_super */
	brelse(bh);
	return ret;
}
