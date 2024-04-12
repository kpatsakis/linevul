void count_bitmap_commit_list(uint32_t *commits, uint32_t *trees,
			      uint32_t *blobs, uint32_t *tags)
{
	assert(bitmap_git.result);

	if (commits)
		*commits = count_object_type(bitmap_git.result, OBJ_COMMIT);

	if (trees)
		*trees = count_object_type(bitmap_git.result, OBJ_TREE);

	if (blobs)
		*blobs = count_object_type(bitmap_git.result, OBJ_BLOB);

	if (tags)
		*tags = count_object_type(bitmap_git.result, OBJ_TAG);
}
