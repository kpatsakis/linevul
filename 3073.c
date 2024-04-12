static void flakey_map_bio(struct dm_target *ti, struct bio *bio)
{
	struct flakey_c *fc = ti->private;

	bio->bi_bdev = fc->dev->bdev;
	if (bio_sectors(bio))
		bio->bi_sector = flakey_map_sector(ti, bio->bi_sector);
}
