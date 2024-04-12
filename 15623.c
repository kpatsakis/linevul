static int asn1_decode_p15_object(sc_context_t *ctx, const u8 *in,
				  size_t len, struct sc_asn1_pkcs15_object *obj,
				  int depth)
{
	struct sc_pkcs15_object *p15_obj = obj->p15_obj;
	struct sc_asn1_entry asn1_c_attr[6], asn1_p15_obj[5];
	struct sc_asn1_entry asn1_ac_rules[SC_PKCS15_MAX_ACCESS_RULES + 1], asn1_ac_rule[SC_PKCS15_MAX_ACCESS_RULES][3];
	size_t flags_len = sizeof(p15_obj->flags);
	size_t label_len = sizeof(p15_obj->label);
	size_t access_mode_len = sizeof(p15_obj->access_rules[0].access_mode);
	int r, ii;

	for (ii=0; ii<SC_PKCS15_MAX_ACCESS_RULES; ii++)
		sc_copy_asn1_entry(c_asn1_access_control_rule, asn1_ac_rule[ii]);
	sc_copy_asn1_entry(c_asn1_access_control_rules, asn1_ac_rules);


	sc_copy_asn1_entry(c_asn1_com_obj_attr, asn1_c_attr);
	sc_copy_asn1_entry(c_asn1_p15_obj, asn1_p15_obj);
	sc_format_asn1_entry(asn1_c_attr + 0, p15_obj->label, &label_len, 0);
	sc_format_asn1_entry(asn1_c_attr + 1, &p15_obj->flags, &flags_len, 0);
	sc_format_asn1_entry(asn1_c_attr + 2, &p15_obj->auth_id, NULL, 0);
	sc_format_asn1_entry(asn1_c_attr + 3, &p15_obj->user_consent, NULL, 0);

	for (ii=0; ii<SC_PKCS15_MAX_ACCESS_RULES; ii++)   {
		sc_format_asn1_entry(asn1_ac_rule[ii] + 0, &p15_obj->access_rules[ii].access_mode, &access_mode_len, 0);
		sc_format_asn1_entry(asn1_ac_rule[ii] + 1, &p15_obj->access_rules[ii].auth_id, NULL, 0);
		sc_format_asn1_entry(asn1_ac_rules + ii, asn1_ac_rule[ii], NULL, 0);
	}
	sc_format_asn1_entry(asn1_c_attr + 4, asn1_ac_rules, NULL, 0);

	sc_format_asn1_entry(asn1_p15_obj + 0, asn1_c_attr, NULL, 0);
	sc_format_asn1_entry(asn1_p15_obj + 1, obj->asn1_class_attr, NULL, 0);
	sc_format_asn1_entry(asn1_p15_obj + 2, obj->asn1_subclass_attr, NULL, 0);
	sc_format_asn1_entry(asn1_p15_obj + 3, obj->asn1_type_attr, NULL, 0);

	r = asn1_decode(ctx, asn1_p15_obj, in, len, NULL, NULL, 0, depth + 1);
	return r;
}
