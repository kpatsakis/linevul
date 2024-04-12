init_config(bool wantExtraInfo  /* = true */)
{
	memset( (char *)ConfigTab, 0, (TABLESIZE * sizeof(BUCKET*)) );
	if (wantExtraInfo) {
		extra_info = new ExtraParamTable();
	} else {
		extra_info = new DummyExtraParamTable();
	}

	param_info_init();

	return;
}
