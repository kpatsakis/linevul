static int entersafe_write_rsa_key_factor(sc_card_t *card,
										  u8 key_id,u8 usage,
										  u8 factor,
										  sc_pkcs15_bignum_t data)
{
	int r;
	sc_apdu_t apdu;

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);

	{/* MSE */
		 u8 sbuff[4];
		 sbuff[0]=0x84;
		 sbuff[1]=0x02;
		 sbuff[2]=key_id;
		 sbuff[3]=usage;

		 sc_format_apdu(card,&apdu,SC_APDU_CASE_3_SHORT,0x22,0x01,0xB8);
		 apdu.data=sbuff;
		 apdu.lc=apdu.datalen=4;
		 
		 r=entersafe_transmit_apdu(card,&apdu,0,0,0,0);
		 SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "APDU transmit failed");
		 SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, sc_check_sw(card, apdu.sw1, apdu.sw2),"Write prkey factor failed(MSE)");
	}

	{/* Write 'x'; */
		u8 sbuff[SC_MAX_APDU_BUFFER_SIZE];

		 sc_format_apdu(card,&apdu,SC_APDU_CASE_3_SHORT,0x46,factor,0x00);

		 memcpy(sbuff,data.data,data.len);
		 entersafe_reverse_buffer(sbuff,data.len);
/*
 *  PK01C and PK13C smart card only support 1024 or 2048bit key .
 *  Size of exponent1 exponent2 coefficient of RSA private key keep the same as size of prime1
 *  So check factor is padded with zero or not
 */
		 switch(factor){
			 case 0x3:
			 case 0x4:
			 case 0x5:
				 {
					 if( data.len > 32 && data.len < 64 )
					 {
						 for(r = data.len ; r < 64 ; r ++)
							 sbuff[r] = 0;
						 data.len = 64;
					 }
					 else if( data.len > 64 && data.len < 128 )
					 {
						 for(r = data.len ; r < 128 ; r ++)
							 sbuff[r] = 0;
						 data.len = 128;
					 }
				 }
				 break;
			 default:
				 break;
		 }

		 apdu.data=sbuff;
		 apdu.lc=apdu.datalen=data.len;

		 r = entersafe_transmit_apdu(card,&apdu,0,0,0,0);
		 SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "APDU transmit failed");
		 SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, sc_check_sw(card, apdu.sw1, apdu.sw2),"Write prkey factor failed");
	}
	SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE,SC_SUCCESS);
}
