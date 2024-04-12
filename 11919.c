bzrtpPacket_t *bzrtp_packetCheck(const uint8_t * input, uint16_t inputLength, uint16_t lastValidSequenceNumber, int *exitCode) {
	bzrtpPacket_t *zrtpPacket;
	uint16_t sequenceNumber;
	uint32_t packetCRC;
	uint16_t messageLength;
	uint32_t messageType;

	/* first check that the packet is a ZRTP one */
	/* is the length compatible with a ZRTP packet */ 
	if ((inputLength<ZRTP_MIN_PACKET_LENGTH) || (inputLength>ZRTP_MAX_PACKET_LENGTH)) {
		 *exitCode = BZRTP_PARSER_ERROR_INVALIDPACKET;
		 return NULL;
	}

	/* check ZRTP packet format from rfc section 5 
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |0 0 0 1|Not Used (set to zero) |         Sequence Number       |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                 Magic Cookie 'ZRTP' (0x5a525450)              |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                        Source Identifier                      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                                                               |
   |           ZRTP Message (length depends on Message Type)       |
   |                            . . .                              |
   |                                                               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                          CRC (1 word)                         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
	if ((input[0]>>4 != 0x01) || (input[4]!= (uint8_t)((ZRTP_MAGIC_COOKIE>>24)&0xFF)) || (input[5]!= (uint8_t)((ZRTP_MAGIC_COOKIE>>16)&0xFF)) || (input[6]!= (uint8_t)((ZRTP_MAGIC_COOKIE>>8)&0xFF)) || (input[7]!= (uint8_t)(ZRTP_MAGIC_COOKIE&0xFF))) {
		*exitCode = BZRTP_PARSER_ERROR_INVALIDPACKET;
		return NULL;
	}

	/* Check the sequence number : it must be > to the last valid one (given in parameter) to discard out of order packets
	 * TODO: what if we got a Sequence Number overflowing the 16 bits ? */
	sequenceNumber = (((uint16_t)input[2])<<8) | ((uint16_t)input[3]);
	if (sequenceNumber <= lastValidSequenceNumber) {
		*exitCode = BZRTP_PARSER_ERROR_OUTOFORDER;
		return NULL;
	}

	/* Check the CRC : The CRC is calculated across the entire ZRTP packet, including the ZRTP header and the ZRTP message, but not including the CRC field.*/
	packetCRC = ((((uint32_t)input[inputLength-4])<<24)&0xFF000000) | ((((uint32_t)input[inputLength-3])<<16)&0x00FF0000) | ((((uint32_t)input[inputLength-2])<<8)&0x0000FF00) | (((uint32_t)input[inputLength-1])&0x000000FF);
	if (bzrtp_CRC32((uint8_t *)input, inputLength - 4) != packetCRC) {
		*exitCode = BZRTP_PARSER_ERROR_INVALIDCRC;
		return NULL;
	}

	/* check message header : 
	 *  0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |0 1 0 1 0 0 0 0 0 1 0 1 1 0 1 0|             length            |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |            Message Type Block            (2 words)            |
   |                                                               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
	if ((input[ZRTP_PACKET_HEADER_LENGTH]!=0x50) || (input[ZRTP_PACKET_HEADER_LENGTH+1]!=0x5a)) {
		*exitCode = BZRTP_PARSER_ERROR_INVALIDMESSAGE;
		return NULL;
	}

	/* get the length from the message: it is expressed in 32bits words, convert it to bytes (4*) */
	messageLength = 4*(((((uint16_t)input[ZRTP_PACKET_HEADER_LENGTH+2])<<8)&0xFF00) | (((uint16_t)input[ZRTP_PACKET_HEADER_LENGTH+3])&0x00FF));

	/* get the message Type */
	messageType = messageTypeStringtoInt((uint8_t *)(input+ZRTP_PACKET_HEADER_LENGTH+4));

	if (messageType == MSGTYPE_INVALID) {
		*exitCode = BZRTP_PARSER_ERROR_INVALIDMESSAGE;
		return NULL;
	}

	/* packet and message seems to be valid, so allocate a structure and parse it */
	zrtpPacket = (bzrtpPacket_t *)malloc(sizeof(bzrtpPacket_t));
	memset(zrtpPacket, 0, sizeof(bzrtpPacket_t));
	zrtpPacket->sequenceNumber = sequenceNumber;
	zrtpPacket->messageLength = messageLength;
	zrtpPacket->messageType = messageType;
	zrtpPacket->messageData = NULL;
	zrtpPacket->packetString = NULL;

	/* get the SSRC */
	zrtpPacket->sourceIdentifier = ((((uint32_t)input[8])<<24)&0xFF000000) | ((((uint32_t)input[9])<<16)&0x00FF0000) | ((((uint32_t)input[10])<<8)&0x0000FF00) | (((uint32_t)input[11])&0x000000FF);

	*exitCode = 0;
	return zrtpPacket;
}
