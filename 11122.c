static int samldb_prim_group_tester(struct samldb_ctx *ac, uint32_t rid)
{
	struct ldb_context *ldb = ldb_module_get_ctx(ac->module);
	struct dom_sid *sid;
	struct ldb_result *res;
	int ret;
	const char * const noattrs[] = { NULL };

	sid = dom_sid_add_rid(ac, samdb_domain_sid(ldb), rid);
	if (sid == NULL) {
		return ldb_operr(ldb);
	}

	ret = dsdb_module_search(ac->module, ac, &res,
				 ldb_get_default_basedn(ldb),
				 LDB_SCOPE_SUBTREE,
				 noattrs, DSDB_FLAG_NEXT_MODULE,
				 ac->req,
				 "(objectSid=%s)",
				 ldap_encode_ndr_dom_sid(ac, sid));
	if (ret != LDB_SUCCESS) {
		return ret;
	}
	if (res->count != 1) {
		talloc_free(res);
		ldb_asprintf_errstring(ldb,
				       "Failed to find primary group with RID %u!",
				       rid);
		return LDB_ERR_UNWILLING_TO_PERFORM;
	}
	talloc_free(res);

	return LDB_SUCCESS;
}
