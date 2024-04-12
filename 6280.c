piv_check_protected_objects(sc_card_t *card)
{
	int r = 0;
	int i;
	piv_private_data_t * priv = PIV_DATA(card);
	u8 buf[8]; /* tag of 53 with 82 xx xx  will fit in 4 */
	u8 * rbuf;
	size_t buf_len;
	static int protected_objects[] = {PIV_OBJ_PI, PIV_OBJ_CHF, PIV_OBJ_IRIS_IMAGE};

	LOG_FUNC_CALLED(card->ctx);
	/*
	 * routine only called from piv_pin_cmd after verify lc=0 did not return 90 00
	 * We will test for a protected object using GET DATA.
	 *
	 * Based on observations, of cards using the GET DATA APDU,
	 * SC_ERROR_SECURITY_STATUS_NOT_SATISFIED  means the PIN not verified,
	 * SC_SUCCESS means PIN has been verified even if it has length 0
	 * SC_ERROR_FILE_NOT_FOUND (which is the bug) does not tell us anything
	 * about the state of the PIN and we will try the next object.
	 *
	 * If we can't determine the security state from this process,
	 * set card_issues CI_CANT_USE_GETDATA_FOR_STATE
	 * and return SC_ERROR_PIN_CODE_INCORRECT
	 * The circumvention is to add a dummy Printed Info object in the card.
	 * so we will have an object to test.
	 *
	 * We save the object's number to use in the future.
	 *
	 */
	if (priv->object_test_verify == 0) {
		for (i = 0; i < (int)(sizeof(protected_objects)/sizeof(int)); i++) {
			buf_len = sizeof(buf);
			priv->pin_cmd_noparse = 1; /* tell piv_general_io dont need to parse at all. */
			rbuf = buf;
			r = piv_get_data(card, protected_objects[i], &rbuf, &buf_len);
			priv->pin_cmd_noparse = 0;
			/* TODO may need to check sw1 and sw2 to see what really happened */
			if (r >= 0 || r == SC_ERROR_SECURITY_STATUS_NOT_SATISFIED) {

				/* we can use this object next time if needed */
				priv->object_test_verify = protected_objects[i];
				break;
			}
		}
		if (priv->object_test_verify == 0) {
			/*
			 * none of the objects returned acceptable sw1, sw2
			 */
			sc_log(card->ctx, "No protected objects found, setting CI_CANT_USE_GETDATA_FOR_STATE");
			priv->card_issues |= CI_CANT_USE_GETDATA_FOR_STATE;
			r = SC_ERROR_PIN_CODE_INCORRECT;
		}
	} else {
		/* use the one object we found earlier. Test is security status has changed */
		buf_len = sizeof(buf);
		priv->pin_cmd_noparse = 1; /* tell piv_general_io dont need to parse at all. */
		rbuf = buf;
		r = piv_get_data(card, priv->object_test_verify, &rbuf, &buf_len);
		priv->pin_cmd_noparse = 0;
	}
	if (r == SC_ERROR_FILE_NOT_FOUND)
		r = SC_ERROR_PIN_CODE_INCORRECT;
	else if (r == SC_ERROR_SECURITY_STATUS_NOT_SATISFIED)
		r = SC_ERROR_PIN_CODE_INCORRECT;
	else if (r > 0)
		r = SC_SUCCESS;

	sc_log(card->ctx, "object_test_verify=%d, card_issues = 0x%08x", priv->object_test_verify, priv->card_issues);
	LOG_FUNC_RETURN(card->ctx, r);
}
