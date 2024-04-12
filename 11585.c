cib_ccm_dispatch(gpointer user_data)
{
    int rc = 0;
    oc_ev_t *ccm_token = (oc_ev_t *) user_data;

    crm_trace("received callback");

    if (ccm_api_handle_event == NULL) {
        ccm_api_handle_event =
            find_library_function(&ccm_library, CCM_LIBRARY, "oc_ev_handle_event", 1);
    }

    rc = (*ccm_api_handle_event) (ccm_token);
    if (0 == rc) {
        return 0;
    }

    crm_err("CCM connection appears to have failed: rc=%d.", rc);

    /* eventually it might be nice to recover and reconnect... but until then... */
    crm_err("Exiting to recover from CCM connection failure");
    crm_exit(2);

    return -1;
}
