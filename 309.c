sort_regions (struct rsvd_region *rsvd_region, int max)
{
	int j;

	/* simple bubble sorting */
	while (max--) {
		for (j = 0; j < max; ++j) {
			if (rsvd_region[j].start > rsvd_region[j+1].start) {
				struct rsvd_region tmp;
				tmp = rsvd_region[j];
				rsvd_region[j] = rsvd_region[j + 1];
				rsvd_region[j + 1] = tmp;
			}
		}
	}
}
