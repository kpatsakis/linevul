static void add_pending_tree(struct rev_info *revs, struct tree *tree)
{
	add_pending_object(revs, &tree->object, "");
}
