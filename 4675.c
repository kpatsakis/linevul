int wvlan_uil_action(struct uilreq *urq, struct wl_private *lp)
{
	int     result = 0;
	ltv_t   *ltv;
	/*------------------------------------------------------------------------*/


	DBG_FUNC("wvlan_uil_action");
	DBG_ENTER(DbgInfo);


	if (urq->hcfCtx == &(lp->hcfCtx)) {
		/* Make sure there's an LTV in the request buffer */
		ltv = (ltv_t *)urq->data;
		if (ltv != NULL) {
			/* Switch on the Type field of the LTV contained in the request
			   buffer */
			switch (ltv->typ) {
			case UIL_ACT_BLOCK:
				DBG_TRACE(DbgInfo, "UIL_ACT_BLOCK\n");
				result = wvlan_uil_block(urq, lp);
				break;
			case UIL_ACT_UNBLOCK:
				DBG_TRACE(DbgInfo, "UIL_ACT_UNBLOCK\n");
				result = wvlan_uil_unblock(urq, lp);
				break;
			case UIL_ACT_SCAN:
				DBG_TRACE(DbgInfo, "UIL_ACT_SCAN\n");
				urq->result = hcf_action(&(lp->hcfCtx), MDD_ACT_SCAN);
				break;
			case UIL_ACT_APPLY:
				DBG_TRACE(DbgInfo, "UIL_ACT_APPLY\n");
				urq->result = wl_apply(lp);
				break;
			case UIL_ACT_RESET:
				DBG_TRACE(DbgInfo, "UIL_ACT_RESET\n");
				urq->result = wl_go(lp);
				break;
			default:
				DBG_WARNING(DbgInfo, "Unknown action code: 0x%x\n", ltv->typ);
				break;
			}
		} else {
			DBG_ERROR(DbgInfo, "Bad LTV for this action\n");
			urq->result = UIL_ERR_LEN;
		}
	} else {
		DBG_ERROR(DbgInfo, "UIL_ERR_WRONG_IFB\n");
		urq->result = UIL_ERR_WRONG_IFB;
	}

	DBG_LEAVE(DbgInfo);
	return result;
} /* wvlan_uil_action */
