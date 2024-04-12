get_ticket_handler(struct ceph_auth_client *ac, int service)
{
	struct ceph_x_ticket_handler *th;
	struct ceph_x_info *xi = ac->private;
	struct rb_node *parent = NULL, **p = &xi->ticket_handlers.rb_node;

	while (*p) {
		parent = *p;
		th = rb_entry(parent, struct ceph_x_ticket_handler, node);
		if (service < th->service)
			p = &(*p)->rb_left;
		else if (service > th->service)
			p = &(*p)->rb_right;
		else
			return th;
	}

	/* add it */
	th = kzalloc(sizeof(*th), GFP_NOFS);
	if (!th)
		return ERR_PTR(-ENOMEM);
	th->service = service;
	rb_link_node(&th->node, parent, p);
	rb_insert_color(&th->node, &xi->ticket_handlers);
	return th;
}
