sc_get_driver(void)
{
	struct sc_card_driver *iso_drv;

	iso_drv = sc_get_iso7816_driver();
	iso_ops = iso_drv->ops;
	gpk_ops = *iso_ops;

	gpk_ops.match_card	= gpk_match_card;
	gpk_ops.init		= gpk_init;
	gpk_ops.finish		= gpk_finish;
	gpk_ops.select_file	= gpk_select_file;
	gpk_ops.read_binary	= gpk_read_binary;
	gpk_ops.write_binary	= gpk_write_binary;
	gpk_ops.update_binary	= gpk_update_binary;
	gpk_ops.create_file	= gpk_create_file;
	/* gpk_ops.check_sw	= gpk_check_sw; */
	gpk_ops.card_ctl	= gpk_card_ctl;
	gpk_ops.set_security_env= gpk_set_security_env;
	gpk_ops.restore_security_env= gpk_restore_security_env;
	gpk_ops.compute_signature= gpk_compute_signature;
	gpk_ops.decipher	= gpk_decipher;
	gpk_ops.pin_cmd		= gpk_pin_cmd;

	return &gpk_drv;
}
