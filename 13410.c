int sm_force_attribute_rewrite(p_fm_config_conx_hdlt hdl, fm_mgr_type_t mgr, int argc, char *argv[]) {
	fm_mgr_config_errno_t	res;
	fm_msg_ret_code_t		ret_code;
	int attrRewrite = 0;
	
	if (argc > 1) {
		printf("Error: only 1 argument expected\n");
		return 0;
	}
	if (argc == 1) {
		attrRewrite = atol(argv[0]);
		if (attrRewrite < 0 || attrRewrite > 1) {
			printf("Error: attrRewrite must be either 0 (disable) or 1 (enable)\n");
			return 0;
		}
	}


	if((res = fm_mgr_simple_query(hdl, FM_ACT_GET, FM_DT_SM_FORCE_ATTRIBUTE_REWRITE, mgr, sizeof(attrRewrite), (void*) &attrRewrite, &ret_code)) != FM_CONF_OK)
	{
		fprintf(stderr, "sm_force_attribute_rewrite: Failed to retrieve data: \n"
		       "\tError:(%d) %s \n\tRet code:(%d) %s\n",
		       res, fm_mgr_get_error_str(res),ret_code,
		       fm_mgr_get_resp_error_str(ret_code));
	} else {
		printf("Successfully sent set to %d of force attribute rewriting to local SM instance\n", attrRewrite);
	}
	return 0;
}
