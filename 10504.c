fm_mgr_pm_cfg_query
(
	IN      p_fm_config_conx_hdlt       hdl,
	IN      fm_mgr_action_t             action,
		OUT pm_config_t                 *info,
		OUT fm_msg_ret_code_t           *ret_code
)
{
	p_hsm_com_client_hdl_t client_hdl;

    if ( (client_hdl = get_mgr_hdl(hdl,FM_MGR_PM)) != NULL )
    {
        return fm_mgr_general_query(client_hdl,action,FM_DT_PM_CFG,sizeof(pm_config_t),info,ret_code);
    }

	return FM_CONF_ERROR;

}
