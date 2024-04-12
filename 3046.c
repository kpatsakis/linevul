static int piv_find_aid(sc_card_t * card, sc_file_t *aid_file)
{
	sc_apdu_t apdu;
	u8 rbuf[SC_MAX_APDU_BUFFER_SIZE];
	int r,i;
	const u8 *tag;
	size_t taglen;
	const u8 *pix;
	size_t pixlen;
	size_t resplen = sizeof(rbuf);

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);

	/* first  see if the default application will return a template
	 * that we know about.
	 */

	r = piv_select_aid(card, piv_aids[0].value, piv_aids[0].len_short, rbuf, &resplen);
	if (r >= 0 && resplen > 2 ) {
		tag = sc_asn1_find_tag(card->ctx, rbuf, resplen, 0x61, &taglen);
		if (tag != NULL) {
			pix = sc_asn1_find_tag(card->ctx, tag, taglen, 0x4F, &pixlen);
			if (pix != NULL ) {
				sc_log(card->ctx, "found PIX");

				/* early cards returned full AID, rather then just the pix */
				for (i = 0; piv_aids[i].len_long != 0; i++) {
					if ((pixlen >= 6 && memcmp(pix, piv_aids[i].value + 5,
									piv_aids[i].len_long - 5 ) == 0)
						 || ((pixlen >=  piv_aids[i].len_short &&
							memcmp(pix, piv_aids[i].value,
							piv_aids[i].len_short) == 0))) {
						if (card->type > SC_CARD_TYPE_PIV_II_BASE &&
							card->type < SC_CARD_TYPE_PIV_II_BASE+1000 &&
							card->type == piv_aids[i].enumtag) {
							LOG_FUNC_RETURN(card->ctx, i);
						} else {
							LOG_FUNC_RETURN(card->ctx, i);
						}
					}
				}
			}
		}
	}

	/* for testing, we can force the use of a specific AID
	 *  by using the card= parameter in conf file
	 */
	for (i = 0; piv_aids[i].len_long != 0; i++) {
		if (card->type > SC_CARD_TYPE_PIV_II_BASE &&
			card->type < SC_CARD_TYPE_PIV_II_BASE+1000 &&
			card->type != piv_aids[i].enumtag) {
				continue;
		}
		sc_format_apdu(card, &apdu, SC_APDU_CASE_4_SHORT, 0xA4, 0x04, 0x00);
		apdu.lc = piv_aids[i].len_long;
		apdu.data = piv_aids[i].value;

		apdu.datalen = apdu.lc;
		apdu.resp = rbuf;
		apdu.resplen = sizeof(rbuf);
		apdu.le = 256;

		r = sc_transmit_apdu(card, &apdu);
		LOG_TEST_RET(card->ctx, r, "APDU transmit failed");

		r = sc_check_sw(card, apdu.sw1, apdu.sw2);
		if (r)  {
			if (card->type != 0 && card->type == piv_aids[i].enumtag)
				LOG_FUNC_RETURN(card->ctx, (r < 0)? r: i);
			continue;
		}

		if ( apdu.resplen == 0 && r == 0) {
			/* could be the MSU card */
			continue; /* other cards will return a FCI */
		}

		if (apdu.resp[0] != 0x6f || apdu.resp[1] > apdu.resplen - 2 )
			SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE, SC_ERROR_NO_CARD_SUPPORT);

		card->ops->process_fci(card, aid_file, apdu.resp+2, apdu.resp[1]);

		LOG_FUNC_RETURN(card->ctx, i);
	}

	LOG_FUNC_RETURN(card->ctx, SC_ERROR_NO_CARD_SUPPORT);
}
