static int linear_map(struct dm_target *ti, struct bio *bio,
		      union map_info *map_context)
{
	linear_map_bio(ti, bio);

	return DM_MAPIO_REMAPPED;
}
