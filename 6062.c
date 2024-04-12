piv_pin_cmd(sc_card_t *card, struct sc_pin_cmd_data *data, int *tries_left)
{
	int r = 0;
	piv_private_data_t * priv = PIV_DATA(card);

	/* Extra validation of (new) PIN during a PIN change request, to
	 * ensure it's not outside the FIPS 201 4.1.6.1 (numeric only) and
	 * FIPS 140-2 (6 character minimum) requirements.
	 */
	struct sc_card_driver *iso_drv = sc_get_iso7816_driver();

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);
	sc_log(card->ctx, "piv_pin_cmd tries_left=%d, logged_in=%d", priv->tries_left, priv->logged_in);
	if (data->cmd == SC_PIN_CMD_CHANGE) {
		int i = 0;
		if (data->pin2.len < 6) {
			return SC_ERROR_INVALID_PIN_LENGTH;
		}
		for(i=0; i < data->pin2.len; ++i) {
			if (!isdigit(data->pin2.data[i])) {
				return SC_ERROR_INVALID_DATA;
			}
		}
	}

	priv->pin_cmd_verify_sw1 = 0x00U;

	if (data->cmd == SC_PIN_CMD_GET_INFO) { /* fill in what we think it should be */
		data->pin1.logged_in = priv->logged_in;
		data->pin1.tries_left = priv->tries_left;
		if (tries_left)
			*tries_left = priv->tries_left;

		/*
		 * If called to check on the login state for a context specific login
		 * return not logged in. Needed because of logic in e6f7373ef066  
		 */
		if (data->pin_type == SC_AC_CONTEXT_SPECIFIC) {
			data->pin1.logged_in = 0;
			 LOG_FUNC_RETURN(card->ctx, SC_SUCCESS);
		}

		if (priv->logged_in == SC_PIN_STATE_LOGGED_IN) {
			/* Avoid status requests when the user is logged in to handle NIST
			 * 800-73-4 Part 2:
			 * The PKI cryptographic function (see Table 4b) is protected with
			 * a “PIN Always” or “OCC Always” access rule. In other words, the
			 * PIN or OCC data must be submitted and verified every time
			 * immediately before a digital signature key operation.  This
			 * ensures cardholder participation every time the private key is
			 * used for digital signature generation */
			LOG_FUNC_RETURN(card->ctx, SC_SUCCESS);
		}
	}

	/*
	 * If this was for a CKU_CONTEXT_SPECFIC login, lock the card one more time.
	 * to avoid any interference from other applications.  
	 * Sc_unlock will be called at a later time after the next card command 
	 * that should be a crypto operation. If its not then it is a error by the 
	 * calling application.
	 */
	if (data->cmd == SC_PIN_CMD_VERIFY && data->pin_type == SC_AC_CONTEXT_SPECIFIC) {
		priv->context_specific = 1;
		sc_log(card->ctx,"Starting CONTEXT_SPECIFIC verify");
		sc_lock(card);
	}

	priv->pin_cmd_verify = 1; /* tell piv_check_sw its a verify to save sw1, sw2 */
	r = iso_drv->ops->pin_cmd(card, data, tries_left);
	priv->pin_cmd_verify = 0;

	/* if verify failed, release the lock */
	if (data->cmd == SC_PIN_CMD_VERIFY && r < 0 &&  priv->context_specific) {
		sc_log(card->ctx,"Clearing CONTEXT_SPECIFIC");
		priv->context_specific = 0;
		sc_unlock(card);
	}

	/* if access to applet is know to be reset by other driver  we select_aid and try again */
	if ( priv->card_issues & CI_OTHER_AID_LOSE_STATE && priv->pin_cmd_verify_sw1 == 0x6DU) {
		sc_log(card->ctx, "AID may be lost doing piv_find_aid and retry pin_cmd");
		piv_find_aid(card, priv->aid_file); /* return not tested */

		priv->pin_cmd_verify = 1; /* tell piv_check_sw its a verify to save sw1, sw2 */
		r = iso_drv->ops->pin_cmd(card, data, tries_left);
		priv->pin_cmd_verify = 0;
	}

	/* If verify worked, we are logged_in */
	if (data->cmd == SC_PIN_CMD_VERIFY) {
	    if (r >= 0)
		priv->logged_in = SC_PIN_STATE_LOGGED_IN;
	    else
		priv->logged_in = SC_PIN_STATE_LOGGED_OUT;
	}

	/* Some cards never return 90 00  for SC_PIN_CMD_GET_INFO even if the card state is verified */
	/* PR 797 has changed the return codes from pin_cmd, and added a data->pin1.logged_in flag */

	if (data->cmd == SC_PIN_CMD_GET_INFO) {
		if (priv->card_issues & CI_CANT_USE_GETDATA_FOR_STATE) {
			sc_log(card->ctx, "CI_CANT_USE_GETDATA_FOR_STATE set, assume logged_in=%d", priv->logged_in);
			data->pin1.logged_in =  priv->logged_in; /* use what ever we saw last */
		} else if (priv->card_issues & CI_VERIFY_LC0_FAIL
			&& priv->pin_cmd_verify_sw1 == 0x63U ) { /* can not use modified return codes from iso->drv->pin_cmd */
				/* try another method, looking at a protected object this may require adding one of these to NEO */
			    r = piv_check_protected_objects(card);
			if (r == SC_SUCCESS)
				data->pin1.logged_in = SC_PIN_STATE_LOGGED_IN;
			else if (r ==  SC_ERROR_PIN_CODE_INCORRECT) {
				if (priv->card_issues & CI_CANT_USE_GETDATA_FOR_STATE) { /* we still can not determine login state */

					data->pin1.logged_in = priv->logged_in; /* may have be set from SC_PIN_CMD_VERIFY */
					/* TODO a reset may have logged us out. need to detect resets */
				} else {
					data->pin1.logged_in = SC_PIN_STATE_LOGGED_OUT;
				}
				r = SC_SUCCESS;
			}
		}
		priv->logged_in = data->pin1.logged_in;
		priv->tries_left = data->pin1.tries_left;
	}

	sc_log(card->ctx, "piv_pin_cmd tries_left=%d, logged_in=%d",priv->tries_left, priv->logged_in);
	LOG_FUNC_RETURN(card->ctx, r);
}
