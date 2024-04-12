int32_t messageTypeStringtoInt(uint8_t messageTypeString[8]) {
	if (memcmp(messageTypeString, "Hello   ", 8) == 0) {
		return MSGTYPE_HELLO;
	} else if (memcmp(messageTypeString, "HelloACK", 8) == 0) {
		return MSGTYPE_HELLOACK;
	} else if (memcmp(messageTypeString, "Commit  ", 8) == 0) {
		return MSGTYPE_COMMIT;
	} else if (memcmp(messageTypeString, "DHPart1 ", 8) == 0) {
		return MSGTYPE_DHPART1;
	} else if (memcmp(messageTypeString, "DHPart2 ", 8) == 0) {
		return MSGTYPE_DHPART2;
	} else if (memcmp(messageTypeString, "Confirm1", 8) == 0) {
		return MSGTYPE_CONFIRM1;
	} else if (memcmp(messageTypeString, "Confirm2", 8) == 0) {
		return MSGTYPE_CONFIRM2;
	} else if (memcmp(messageTypeString, "Conf2ACK", 8) == 0) {
		return MSGTYPE_CONF2ACK;
	} else if (memcmp(messageTypeString, "Error   ", 8) == 0) {
		return MSGTYPE_ERROR;
	} else if (memcmp(messageTypeString, "ErrorACK", 8) == 0) {
		return MSGTYPE_ERRORACK;
	} else if (memcmp(messageTypeString, "GoClear ", 8) == 0) {
		return MSGTYPE_GOCLEAR;
	} else if (memcmp(messageTypeString, "ClearACK", 8) == 0) {
		return MSGTYPE_CLEARACK;
	} else if (memcmp(messageTypeString, "SASrelay", 8) == 0) {
		return MSGTYPE_SASRELAY;
	} else if (memcmp(messageTypeString, "RelayACK", 8) == 0) {
		return MSGTYPE_RELAYACK;
	} else if (memcmp(messageTypeString, "Ping    ", 8) == 0) {
		return MSGTYPE_PING;
	} else if (memcmp(messageTypeString, "PingACK ", 8) == 0) {
		return MSGTYPE_PINGACK;
	} else {
		return MSGTYPE_INVALID;
	}
}
