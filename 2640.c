static struct posix_acl *reiserfs_posix_acl_from_disk(const void *value, size_t size)
{
	const char *end = (char *)value + size;
	int n, count;
	struct posix_acl *acl;

	if (!value)
		return NULL;
	if (size < sizeof(reiserfs_acl_header))
		return ERR_PTR(-EINVAL);
	if (((reiserfs_acl_header *) value)->a_version !=
	    cpu_to_le32(REISERFS_ACL_VERSION))
		return ERR_PTR(-EINVAL);
	value = (char *)value + sizeof(reiserfs_acl_header);
	count = reiserfs_acl_count(size);
	if (count < 0)
		return ERR_PTR(-EINVAL);
	if (count == 0)
		return NULL;
	acl = posix_acl_alloc(count, GFP_NOFS);
	if (!acl)
		return ERR_PTR(-ENOMEM);
	for (n = 0; n < count; n++) {
		reiserfs_acl_entry *entry = (reiserfs_acl_entry *) value;
		if ((char *)value + sizeof(reiserfs_acl_entry_short) > end)
			goto fail;
		acl->a_entries[n].e_tag = le16_to_cpu(entry->e_tag);
		acl->a_entries[n].e_perm = le16_to_cpu(entry->e_perm);
		switch (acl->a_entries[n].e_tag) {
		case ACL_USER_OBJ:
		case ACL_GROUP_OBJ:
		case ACL_MASK:
		case ACL_OTHER:
			value = (char *)value +
			    sizeof(reiserfs_acl_entry_short);
			break;

		case ACL_USER:
			value = (char *)value + sizeof(reiserfs_acl_entry);
			if ((char *)value > end)
				goto fail;
			acl->a_entries[n].e_uid = 
				make_kuid(&init_user_ns,
					  le32_to_cpu(entry->e_id));
			break;
		case ACL_GROUP:
			value = (char *)value + sizeof(reiserfs_acl_entry);
			if ((char *)value > end)
				goto fail;
			acl->a_entries[n].e_gid =
				make_kgid(&init_user_ns,
					  le32_to_cpu(entry->e_id));
			break;

		default:
			goto fail;
		}
	}
	if (value != end)
		goto fail;
	return acl;

fail:
	posix_acl_release(acl);
	return ERR_PTR(-EINVAL);
}
