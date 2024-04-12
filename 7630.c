void tee_obj_attr_clear(struct tee_obj *o)
{
	const struct tee_cryp_obj_type_props *tp;
	size_t n;

	if (!o->attr)
		return;
	tp = tee_svc_find_type_props(o->info.objectType);
	if (!tp)
		return;

	for (n = 0; n < tp->num_type_attrs; n++) {
		const struct tee_cryp_obj_type_attrs *ta = tp->type_attrs + n;

		attr_ops[ta->ops_index].clear((uint8_t *)o->attr +
					      ta->raw_offs);
	}
}
