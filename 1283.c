void btm_sec_role_changed (void *p_ref_data)
{
    tBTM_SEC_DEV_REC *p_dev_rec = (tBTM_SEC_DEV_REC *)p_ref_data;
    UINT8 res;

    BTM_TRACE_EVENT ("Security Manager: role changed");

 /* If this role switch was started by peer do not need to do anything */
 if (p_dev_rec->sec_state != BTM_SEC_STATE_SWITCHING_ROLE)
 return;

 /* If serurity required was to FORCE switch and it failed, notify the waiting layer */
 if (((p_dev_rec->security_required & BTM_SEC_FORCE_MASTER) && !p_dev_rec->role_master)
 || ((p_dev_rec->security_required & BTM_SEC_FORCE_SLAVE) &&  p_dev_rec->role_master))
 {
        btm_sec_dev_rec_cback_event (p_dev_rec, BTM_ERR_PROCESSING, FALSE);
 return;
 }

    p_dev_rec->sec_flags |= BTM_SEC_ROLE_SWITCHED;

    p_dev_rec->security_required &= ~(BTM_SEC_FORCE_MASTER | BTM_SEC_ATTEMPT_MASTER |
                                      BTM_SEC_FORCE_SLAVE  | BTM_SEC_ATTEMPT_SLAVE);

    p_dev_rec->sec_state = BTM_SEC_STATE_IDLE;

 if ((res = (UINT8)btm_sec_execute_procedure (p_dev_rec)) != BTM_CMD_STARTED)
 {
        btm_sec_dev_rec_cback_event (p_dev_rec, res, FALSE);
 }
}
