static void __update_nat_bits(struct f2fs_sb_info *sbi, nid_t start_nid,
						struct page *page)
{
	struct f2fs_nm_info *nm_i = NM_I(sbi);
	unsigned int nat_index = start_nid / NAT_ENTRY_PER_BLOCK;
	struct f2fs_nat_block *nat_blk = page_address(page);
	int valid = 0;
	int i;

	if (!enabled_nat_bits(sbi, NULL))
		return;

	for (i = 0; i < NAT_ENTRY_PER_BLOCK; i++) {
		if (start_nid == 0 && i == 0)
			valid++;
		if (nat_blk->entries[i].block_addr)
			valid++;
	}
	if (valid == 0) {
		__set_bit_le(nat_index, nm_i->empty_nat_bits);
		__clear_bit_le(nat_index, nm_i->full_nat_bits);
		return;
	}

	__clear_bit_le(nat_index, nm_i->empty_nat_bits);
	if (valid == NAT_ENTRY_PER_BLOCK)
		__set_bit_le(nat_index, nm_i->full_nat_bits);
	else
		__clear_bit_le(nat_index, nm_i->full_nat_bits);
}
