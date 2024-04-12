static int in_bitmapped_pack(struct object_list *roots)
{
	while (roots) {
		struct object *object = roots->item;
		roots = roots->next;

		if (find_pack_entry_one(object->oid.hash, bitmap_git.pack) > 0)
			return 1;
	}

	return 0;
}
