uint8_t *messageTypeInttoString(uint32_t messageType) {

	switch(messageType) {
		case MSGTYPE_HELLO : 
			return (uint8_t *)"Hello   ";
			break;
		case MSGTYPE_HELLOACK : 
			return (uint8_t *)"HelloACK";
			break;
		case MSGTYPE_COMMIT : 
			return (uint8_t *)"Commit  ";
			break;
		case MSGTYPE_DHPART1 : 
			return (uint8_t *)"DHPart1 ";
			break;
		case MSGTYPE_DHPART2 : 
			return (uint8_t *)"DHPart2 ";
			break;
		case MSGTYPE_CONFIRM1 : 
			return (uint8_t *)"Confirm1";
			break;
		case MSGTYPE_CONFIRM2 : 
			return (uint8_t *)"Confirm2";
			break;
		case MSGTYPE_CONF2ACK : 
			return (uint8_t *)"Conf2ACK";
			break;
		case MSGTYPE_ERROR : 
			return (uint8_t *)"Error   ";
			break;
		case MSGTYPE_ERRORACK : 
			return (uint8_t *)"ErrorACK";
			break;
		case MSGTYPE_GOCLEAR : 
			return (uint8_t *)"GoClear ";
			break;
		case MSGTYPE_CLEARACK : 
			return (uint8_t *)"ClearACK";
			break;
		case MSGTYPE_SASRELAY : 
			return (uint8_t *)"SASrelay";
			break;
		case MSGTYPE_RELAYACK : 
			return (uint8_t *)"RelayACK";
			break;
		case MSGTYPE_PING : 
			return (uint8_t *)"Ping    ";
			break;
		case MSGTYPE_PINGACK : 
			return (uint8_t *)"PingACK ";
			break;
	}
	return NULL;
}
