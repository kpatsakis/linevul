static void add_pending_object_with_mode(struct rev_info *revs,
					 struct object *obj,
					 const char *name, unsigned mode)
{
	add_pending_object_with_path(revs, obj, name, mode, NULL);
}
