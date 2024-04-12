static int entersafe_set_security_env(sc_card_t *card,
									  const sc_security_env_t *env,
									  int se_num)
{
	 assert(card);
	 assert(env);

	 SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);

	 if(card->drv_data){
		  free(card->drv_data);
		  card->drv_data=0;
	 }

	 card->drv_data = calloc(1,sizeof(*env));
	 if(!card->drv_data)
		  SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE, SC_ERROR_OUT_OF_MEMORY);

	 memcpy(card->drv_data,env,sizeof(*env));
	 SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE, SC_SUCCESS);
}
