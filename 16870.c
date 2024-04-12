int sm_skip_attr_write(p_fm_config_conx_hdlt hdl, fm_mgr_type_t mgr, int argc, char *argv[]) {
	fm_mgr_config_errno_t	res;
	fm_msg_ret_code_t		ret_code;
	unsigned int attrSkip = 0;

	if (argc > 1) {
		printf("Error: only 1 argument or less expected\n");
		return 0;
	}
	if ((argc==0) || ((argc==1) && (strcmp(argv[0],"-help")==0)) ) {
		printf(" SM SKIP WRITE BITMASKS...\n");
		printf("   SM_SKIP_WRITE_PORTINFO   0x00000001  (Includes Port Info)\n");
		printf("   SM_SKIP_WRITE_SMINFO     0x00000002  (Includes Sm Info)\n");
		printf("   SM_SKIP_WRITE_GUID       0x00000004  (Includes GUID Info\n");
		printf("   SM_SKIP_WRITE_SWITCHINFO 0x00000008  (Includes Switch Info\n");
		printf("   SM_SKIP_WRITE_SWITCHLTV  0x00000010  (Includes Switch LTV)\n");
		printf("   SM_SKIP_WRITE_VLARB      0x00000020  (Includes VLArb Tables/Preempt Tables)\n");
		printf("   SM_SKIP_WRITE_MAPS       0x00000040  (Includes SL::SC, SC::SL, SC::VL)\n");
		printf("   SM_SKIP_WRITE_LFT        0x00000080  (Includes LFT, MFT)\n");
		printf("   SM_SKIP_WRITE_AR         0x00000100  (Includes PG table, PG FDB)\n");
		printf("   SM_SKIP_WRITE_PKEY       0x00000200\n");
		printf("   SM_SKIP_WRITE_CONG       0x00000400  (Includes HFI / Switch congestion)\n");
		printf("   SM_SKIP_WRITE_BFRCTRL    0x00000800\n");
		printf("   SM_SKIP_WRITE_NOTICE     0x00001000\n");
		return  0;
	}

	attrSkip = strtol(argv[0],NULL,0);

	if((res = fm_mgr_simple_query(hdl, FM_ACT_GET, FM_DT_SM_SKIP_ATTRIBUTE_WRITE, mgr, sizeof(attrSkip), (void*) &attrSkip, &ret_code)) != FM_CONF_OK) {
		fprintf(stderr, "sm_skip_attr_write: Failed to retrieve data: \n"
			   "\tError:(%d) %s \n\tRet code:(%d) %s\n",
			   res, fm_mgr_get_error_str(res),ret_code,
			   fm_mgr_get_resp_error_str(ret_code));
	} else {
		printf("Successfully sent set to 0x%x of skip write to local SM instance\n", attrSkip);
	}
	return 0;
 }
