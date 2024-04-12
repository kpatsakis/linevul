struct ctl_table_header *__sysctl_head_next(struct nsproxy *namespaces,
					    struct ctl_table_header *prev)
{
	struct ctl_table_root *root;
	struct list_head *header_list;
	struct ctl_table_header *head;
	struct list_head *tmp;

	spin_lock(&sysctl_lock);
	if (prev) {
		head = prev;
		tmp = &prev->ctl_entry;
		unuse_table(prev);
		goto next;
	}
	tmp = &root_table_header.ctl_entry;
	for (;;) {
		head = list_entry(tmp, struct ctl_table_header, ctl_entry);

		if (!use_table(head))
			goto next;
		spin_unlock(&sysctl_lock);
		return head;
	next:
		root = head->root;
		tmp = tmp->next;
		header_list = lookup_header_list(root, namespaces);
		if (tmp != header_list)
			continue;

		do {
			root = list_entry(root->root_list.next,
					struct ctl_table_root, root_list);
			if (root == &sysctl_table_root)
				goto out;
			header_list = lookup_header_list(root, namespaces);
		} while (list_empty(header_list));
		tmp = header_list->next;
	}
out:
	spin_unlock(&sysctl_lock);
	return NULL;
}
