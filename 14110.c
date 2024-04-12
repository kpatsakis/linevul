xfs_attr_rmtval_copyout(
	struct xfs_mount *mp,
	struct xfs_buf	*bp,
	xfs_ino_t	ino,
	int		*offset,
	int		*valuelen,
	__uint8_t	**dst)
{
	char		*src = bp->b_addr;
	xfs_daddr_t	bno = bp->b_bn;
	int		len = BBTOB(bp->b_length);

	ASSERT(len >= XFS_LBSIZE(mp));

	while (len > 0 && *valuelen > 0) {
		int hdr_size = 0;
		int byte_cnt = XFS_ATTR3_RMT_BUF_SPACE(mp, XFS_LBSIZE(mp));

		byte_cnt = min(*valuelen, byte_cnt);

		if (xfs_sb_version_hascrc(&mp->m_sb)) {
			if (!xfs_attr3_rmt_hdr_ok(mp, src, ino, *offset,
						  byte_cnt, bno)) {
				xfs_alert(mp,
"remote attribute header mismatch bno/off/len/owner (0x%llx/0x%x/Ox%x/0x%llx)",
					bno, *offset, byte_cnt, ino);
				return EFSCORRUPTED;
			}
			hdr_size = sizeof(struct xfs_attr3_rmt_hdr);
		}

		memcpy(*dst, src + hdr_size, byte_cnt);

		/* roll buffer forwards */
		len -= XFS_LBSIZE(mp);
		src += XFS_LBSIZE(mp);
		bno += mp->m_bsize;

		/* roll attribute data forwards */
		*valuelen -= byte_cnt;
		*dst += byte_cnt;
		*offset += byte_cnt;
	}
	return 0;
}
