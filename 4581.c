bt_status_t btif_dm_start_discovery(void)
{
    tBTA_DM_INQ inq_params;
    tBTA_SERVICE_MASK services = 0;
    tBTA_DM_BLE_PF_FILT_PARAMS adv_filt_param;

    BTIF_TRACE_EVENT("%s", __FUNCTION__);

#if (defined(BLE_INCLUDED) && (BLE_INCLUDED == TRUE))
    memset(&adv_filt_param, 0, sizeof(tBTA_DM_BLE_PF_FILT_PARAMS));
 /* Cleanup anything remaining on index 0 */
    BTA_DmBleScanFilterSetup(BTA_DM_BLE_SCAN_COND_DELETE, 0, &adv_filt_param, NULL,
                             bte_scan_filt_param_cfg_evt, 0);

 /* Add an allow-all filter on index 0*/
    adv_filt_param.dely_mode = IMMEDIATE_DELY_MODE;
    adv_filt_param.feat_seln = ALLOW_ALL_FILTER;
    adv_filt_param.filt_logic_type = BTA_DM_BLE_PF_FILT_LOGIC_OR;
    adv_filt_param.list_logic_type = BTA_DM_BLE_PF_LIST_LOGIC_OR;
    adv_filt_param.rssi_low_thres = LOWEST_RSSI_VALUE;
    adv_filt_param.rssi_high_thres = LOWEST_RSSI_VALUE;
    BTA_DmBleScanFilterSetup(BTA_DM_BLE_SCAN_COND_ADD, 0, &adv_filt_param, NULL,
                             bte_scan_filt_param_cfg_evt, 0);

 /* TODO: Do we need to handle multiple inquiries at the same time? */

 /* Set inquiry params and call API */
    inq_params.mode = BTA_DM_GENERAL_INQUIRY|BTA_BLE_GENERAL_INQUIRY;
#if (defined(BTA_HOST_INTERLEAVE_SEARCH) && BTA_HOST_INTERLEAVE_SEARCH == TRUE)
    inq_params.intl_duration[0]= BTIF_DM_INTERLEAVE_DURATION_BR_ONE;
    inq_params.intl_duration[1]= BTIF_DM_INTERLEAVE_DURATION_LE_ONE;
    inq_params.intl_duration[2]= BTIF_DM_INTERLEAVE_DURATION_BR_TWO;
    inq_params.intl_duration[3]= BTIF_DM_INTERLEAVE_DURATION_LE_TWO;
#endif
#else
    inq_params.mode = BTA_DM_GENERAL_INQUIRY;
#endif
    inq_params.duration = BTIF_DM_DEFAULT_INQ_MAX_DURATION;

    inq_params.max_resps = BTIF_DM_DEFAULT_INQ_MAX_RESULTS;
    inq_params.report_dup = TRUE;

    inq_params.filter_type = BTA_DM_INQ_CLR;
 /* TODO: Filter device by BDA needs to be implemented here */

 /* Will be enabled to TRUE once inquiry busy level has been received */
    btif_dm_inquiry_in_progress = FALSE;
 /* find nearby devices */
    BTA_DmSearch(&inq_params, services, bte_search_devices_evt);

 return BT_STATUS_SUCCESS;
}
