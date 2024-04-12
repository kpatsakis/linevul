void test_parserComplete() {

	int retval;
	/* alice's maintained packet */
	bzrtpPacket_t *alice_Hello, *alice_HelloFromBob, *alice_HelloACK, *alice_HelloACKFromBob;
	/* bob's maintained packet */
	bzrtpPacket_t *bob_Hello, *bob_HelloFromAlice, *bob_HelloACK, *bob_HelloACKFromAlice;
	/* Create zrtp Context */
	bzrtpContext_t *contextAlice = bzrtp_createBzrtpContext(0x12345678); /* Alice's SSRC of main channel is 12345678 */
	bzrtpContext_t *contextBob = bzrtp_createBzrtpContext(0x87654321); /* Bob's SSRC of main channel is 87654321 */

	bzrtpHelloMessage_t *alice_HelloFromBob_message;
	bzrtpHelloMessage_t *bob_HelloFromAlice_message;
	bzrtpPacket_t *alice_selfDHPart;
	bzrtpPacket_t *bob_selfDHPart;
	bzrtpPacket_t *alice_Commit;
	bzrtpPacket_t *bob_Commit;
	bzrtpPacket_t *bob_CommitFromAlice;
	bzrtpPacket_t *alice_CommitFromBob;
	uint8_t tmpBuffer[8];
	bzrtpDHPartMessage_t *bob_DHPart1;
	bzrtpPacket_t *alice_DHPart1FromBob;
	bzrtpDHPartMessage_t *alice_DHPart1FromBob_message=NULL;
	bzrtpPacket_t *bob_DHPart2FromAlice;
	bzrtpDHPartMessage_t *bob_DHPart2FromAlice_message=NULL;
	uint16_t secretLength;
	uint16_t totalHashDataLength;
	uint8_t *dataToHash;
	uint16_t hashDataIndex = 0;
	uint8_t alice_totalHash[32]; /* Note : actual length of hash depends on the choosen algo */
	uint8_t bob_totalHash[32]; /* Note : actual length of hash depends on the choosen algo */
	uint8_t *s1=NULL;
	uint32_t s1Length=0;
	uint8_t *s2=NULL;
	uint32_t s2Length=0;
	uint8_t *s3=NULL;
	uint32_t s3Length=0;
	uint8_t alice_sasHash[32];
	uint8_t bob_sasHash[32];
	uint32_t sasValue;
	char sas[32];
	bzrtpPacket_t *bob_Confirm1;
	bzrtpPacket_t *alice_Confirm1FromBob;
	bzrtpConfirmMessage_t *alice_Confirm1FromBob_message=NULL;
	bzrtpPacket_t *alice_Confirm2;
	bzrtpPacket_t *bob_Confirm2FromAlice;
	bzrtpConfirmMessage_t *bob_Confirm2FromAlice_message=NULL;
	bzrtpPacket_t *bob_Conf2ACK;
	bzrtpPacket_t *alice_Conf2ACKFromBob;
	bzrtpPacket_t *alice_Confirm1;
	bzrtpPacket_t *bob_Confirm1FromAlice;
	bzrtpConfirmMessage_t *bob_Confirm1FromAlice_message=NULL;
	bzrtpPacket_t *bob_Confirm2;
	bzrtpPacket_t *alice_Confirm2FromBob;
	bzrtpConfirmMessage_t *alice_Confirm2FromBob_message=NULL;
	bzrtpPacket_t *alice_Conf2ACK;
	bzrtpPacket_t *bob_Conf2ACKFromAlice;
	bzrtpCallbacks_t cbs={0};

	/* Create the client context, used for zidFilename only */
	my_Context_t clientContextAlice;
	my_Context_t clientContextBob;
	strcpy(clientContextAlice.zidFilename, "./ZIDAlice.txt");
	strcpy(clientContextBob.zidFilename, "./ZIDBob.txt");

	/* attach the clientContext to the bzrtp Context */
	retval = bzrtp_setClientData(contextAlice, 0x12345678, (void *)&clientContextAlice);
	retval += bzrtp_setClientData(contextBob, 0x87654321, (void *)&clientContextBob);

	/* set the cache related callback functions */
	cbs.bzrtp_loadCache=floadAlice;
	cbs.bzrtp_writeCache=fwriteAlice;

	bzrtp_setCallbacks(contextAlice, &cbs);

	cbs.bzrtp_loadCache=floadBob;
	cbs.bzrtp_writeCache=fwriteBob;
	bzrtp_setCallbacks(contextBob, &cbs);

	bzrtp_message ("Init the contexts\n");
	/* end the context init */
	bzrtp_initBzrtpContext(contextAlice);
	bzrtp_initBzrtpContext(contextBob);

	/* now create Alice and BOB Hello packet */
	alice_Hello = bzrtp_createZrtpPacket(contextAlice, contextAlice->channelContext[0], MSGTYPE_HELLO, &retval);
	if (bzrtp_packetBuild(contextAlice, contextAlice->channelContext[0], alice_Hello, contextAlice->channelContext[0]->selfSequenceNumber) ==0) {
		contextAlice->channelContext[0]->selfSequenceNumber++;
		contextAlice->channelContext[0]->selfPackets[HELLO_MESSAGE_STORE_ID] = alice_Hello;
	}
	bob_Hello = bzrtp_createZrtpPacket(contextBob, contextBob->channelContext[0], MSGTYPE_HELLO, &retval);
	if (bzrtp_packetBuild(contextBob, contextBob->channelContext[0], bob_Hello, contextBob->channelContext[0]->selfSequenceNumber) ==0) {
		contextBob->channelContext[0]->selfSequenceNumber++;
		contextBob->channelContext[0]->selfPackets[HELLO_MESSAGE_STORE_ID] = bob_Hello;
	}

	/* now send Alice Hello's to Bob and vice-versa, so they parse them */
	alice_HelloFromBob = bzrtp_packetCheck(bob_Hello->packetString, bob_Hello->messageLength+16, contextAlice->channelContext[0]->peerSequenceNumber, &retval);
	retval +=  bzrtp_packetParser(contextAlice, contextAlice->channelContext[0], bob_Hello->packetString, bob_Hello->messageLength+16, alice_HelloFromBob);
	bzrtp_message ("Alice parsing returns %x\n", retval);
	if (retval==0) {
		bzrtpHelloMessage_t *alice_HelloFromBob_message;
		int i;

		contextAlice->channelContext[0]->peerSequenceNumber = alice_HelloFromBob->sequenceNumber;
		/* save bob's Hello packet in Alice's context */
		contextAlice->channelContext[0]->peerPackets[HELLO_MESSAGE_STORE_ID] = alice_HelloFromBob;

		/* determine crypto Algo to use */
		alice_HelloFromBob_message = (bzrtpHelloMessage_t *)alice_HelloFromBob->messageData;
		retval = crypoAlgoAgreement(contextAlice, contextAlice->channelContext[0], contextAlice->channelContext[0]->peerPackets[HELLO_MESSAGE_STORE_ID]->messageData);
		if (retval == 0) {
			bzrtp_message ("Alice selected algo %x\n", contextAlice->channelContext[0]->keyAgreementAlgo);
			memcpy(contextAlice->peerZID, alice_HelloFromBob_message->ZID, 12);
		}

		/* check if the peer accept MultiChannel */
		for (i=0; i<alice_HelloFromBob_message->kc; i++) {
			if (alice_HelloFromBob_message->supportedKeyAgreement[i] == ZRTP_KEYAGREEMENT_Mult) {
				contextAlice->peerSupportMultiChannel = 1;
			}
		}
	}

	bob_HelloFromAlice = bzrtp_packetCheck(alice_Hello->packetString, alice_Hello->messageLength+16, contextBob->channelContext[0]->peerSequenceNumber, &retval);
	retval +=  bzrtp_packetParser(contextBob, contextBob->channelContext[0], alice_Hello->packetString, alice_Hello->messageLength+16, bob_HelloFromAlice);
	bzrtp_message ("Bob parsing returns %x\n", retval);
	if (retval==0) {
		bzrtpHelloMessage_t *bob_HelloFromAlice_message;
		int i;

		contextBob->channelContext[0]->peerSequenceNumber = bob_HelloFromAlice->sequenceNumber;
		/* save alice's Hello packet in bob's context */
		contextBob->channelContext[0]->peerPackets[HELLO_MESSAGE_STORE_ID] = bob_HelloFromAlice;

		/* determine crypto Algo to use */
		bob_HelloFromAlice_message = (bzrtpHelloMessage_t *)bob_HelloFromAlice->messageData;
		retval = crypoAlgoAgreement(contextBob, contextBob->channelContext[0], contextBob->channelContext[0]->peerPackets[HELLO_MESSAGE_STORE_ID]->messageData);
		if (retval == 0) {
			bzrtp_message ("Bob selected algo %x\n", contextBob->channelContext[0]->keyAgreementAlgo);
			memcpy(contextBob->peerZID, bob_HelloFromAlice_message->ZID, 12);
		}

		/* check if the peer accept MultiChannel */
		for (i=0; i<bob_HelloFromAlice_message->kc; i++) {
			if (bob_HelloFromAlice_message->supportedKeyAgreement[i] == ZRTP_KEYAGREEMENT_Mult) {
				contextBob->peerSupportMultiChannel = 1;
			}
		}
	}

	/* update context with hello message information : H3  and compute initiator and responder's shared secret Hashs */
	alice_HelloFromBob_message = (bzrtpHelloMessage_t *)alice_HelloFromBob->messageData;
	memcpy(contextAlice->channelContext[0]->peerH[3], alice_HelloFromBob_message->H3, 32);
	bob_HelloFromAlice_message = (bzrtpHelloMessage_t *)bob_HelloFromAlice->messageData;
	memcpy(contextBob->channelContext[0]->peerH[3], bob_HelloFromAlice_message->H3, 32);

	/* get the secrets associated to peer ZID */
	bzrtp_getPeerAssociatedSecretsHash(contextAlice, alice_HelloFromBob_message->ZID);
	bzrtp_getPeerAssociatedSecretsHash(contextBob, bob_HelloFromAlice_message->ZID);

	/* compute the initiator hashed secret as in rfc section 4.3.1 */
	if (contextAlice->cachedSecret.rs1!=NULL) {
		contextAlice->channelContext[0]->hmacFunction(contextAlice->cachedSecret.rs1, contextAlice->cachedSecret.rs1Length, (uint8_t *)"Initiator", 9, 8, contextAlice->initiatorCachedSecretHash.rs1ID);
	} else { /* we have no secret, generate a random */
		bctoolbox_rng_get(contextAlice->RNGContext, contextAlice->initiatorCachedSecretHash.rs1ID, 8);
	}

	if (contextAlice->cachedSecret.rs2!=NULL) {
		contextAlice->channelContext[0]->hmacFunction(contextAlice->cachedSecret.rs2, contextAlice->cachedSecret.rs2Length, (uint8_t *)"Initiator", 9, 8, contextAlice->initiatorCachedSecretHash.rs2ID);
	} else { /* we have no secret, generate a random */
		bctoolbox_rng_get(contextAlice->RNGContext, contextAlice->initiatorCachedSecretHash.rs2ID, 8);
	}

	if (contextAlice->cachedSecret.auxsecret!=NULL) {
		contextAlice->channelContext[0]->hmacFunction(contextAlice->cachedSecret.auxsecret, contextAlice->cachedSecret.auxsecretLength, contextAlice->channelContext[0]->selfH[3], 32, 8, contextAlice->channelContext[0]->initiatorAuxsecretID);
	} else { /* we have no secret, generate a random */
		bctoolbox_rng_get(contextAlice->RNGContext, contextAlice->channelContext[0]->initiatorAuxsecretID, 8);
	}

	if (contextAlice->cachedSecret.pbxsecret!=NULL) {
		contextAlice->channelContext[0]->hmacFunction(contextAlice->cachedSecret.pbxsecret, contextAlice->cachedSecret.pbxsecretLength, (uint8_t *)"Initiator", 9, 8, contextAlice->initiatorCachedSecretHash.pbxsecretID);
	} else { /* we have no secret, generate a random */
		bctoolbox_rng_get(contextAlice->RNGContext, contextAlice->initiatorCachedSecretHash.pbxsecretID, 8);
	}

	if (contextAlice->cachedSecret.rs1!=NULL) {
		contextAlice->channelContext[0]->hmacFunction(contextAlice->cachedSecret.rs1, contextAlice->cachedSecret.rs1Length, (uint8_t *)"Responder", 9, 8, contextAlice->responderCachedSecretHash.rs1ID);
	} else { /* we have no secret, generate a random */
		bctoolbox_rng_get(contextAlice->RNGContext, contextAlice->responderCachedSecretHash.rs1ID, 8);
	}

	if (contextAlice->cachedSecret.rs2!=NULL) {
		contextAlice->channelContext[0]->hmacFunction(contextAlice->cachedSecret.rs2, contextAlice->cachedSecret.rs2Length, (uint8_t *)"Responder", 9, 8, contextAlice->responderCachedSecretHash.rs2ID);
	} else { /* we have no secret, generate a random */
		bctoolbox_rng_get(contextAlice->RNGContext, contextAlice->responderCachedSecretHash.rs2ID, 8);
	}

	if (contextAlice->cachedSecret.auxsecret!=NULL) {
		contextAlice->channelContext[0]->hmacFunction(contextAlice->cachedSecret.auxsecret, contextAlice->cachedSecret.auxsecretLength, contextAlice->channelContext[0]->peerH[3], 32, 8, contextAlice->channelContext[0]->responderAuxsecretID);
	} else { /* we have no secret, generate a random */
		bctoolbox_rng_get(contextAlice->RNGContext, contextAlice->channelContext[0]->responderAuxsecretID, 8);
	}

	if (contextAlice->cachedSecret.pbxsecret!=NULL) {
		contextAlice->channelContext[0]->hmacFunction(contextAlice->cachedSecret.pbxsecret, contextAlice->cachedSecret.pbxsecretLength, (uint8_t *)"Responder", 9, 8, contextAlice->responderCachedSecretHash.pbxsecretID);
	} else { /* we have no secret, generate a random */
		bctoolbox_rng_get(contextAlice->RNGContext, contextAlice->responderCachedSecretHash.pbxsecretID, 8);
	}


	/* Bob hashes*/
	if (contextBob->cachedSecret.rs1!=NULL) {
		contextBob->channelContext[0]->hmacFunction(contextBob->cachedSecret.rs1, contextBob->cachedSecret.rs1Length, (uint8_t *)"Initiator", 9, 8, contextBob->initiatorCachedSecretHash.rs1ID);
	} else { /* we have no secret, generate a random */
		bctoolbox_rng_get(contextBob->RNGContext, contextBob->initiatorCachedSecretHash.rs1ID, 8);
	}

	if (contextBob->cachedSecret.rs2!=NULL) {
		contextBob->channelContext[0]->hmacFunction(contextBob->cachedSecret.rs2, contextBob->cachedSecret.rs2Length, (uint8_t *)"Initiator", 9, 8, contextBob->initiatorCachedSecretHash.rs2ID);
	} else { /* we have no secret, generate a random */
		bctoolbox_rng_get(contextBob->RNGContext, contextBob->initiatorCachedSecretHash.rs2ID, 8);
	}

	if (contextBob->cachedSecret.auxsecret!=NULL) {
		contextBob->channelContext[0]->hmacFunction(contextBob->cachedSecret.auxsecret, contextBob->cachedSecret.auxsecretLength, contextBob->channelContext[0]->selfH[3], 32, 8, contextBob->channelContext[0]->initiatorAuxsecretID);
	} else { /* we have no secret, generate a random */
		bctoolbox_rng_get(contextBob->RNGContext, contextBob->channelContext[0]->initiatorAuxsecretID, 8);
	}

	if (contextBob->cachedSecret.pbxsecret!=NULL) {
		contextBob->channelContext[0]->hmacFunction(contextBob->cachedSecret.pbxsecret, contextBob->cachedSecret.pbxsecretLength, (uint8_t *)"Initiator", 9, 8, contextBob->initiatorCachedSecretHash.pbxsecretID);
	} else { /* we have no secret, generate a random */
		bctoolbox_rng_get(contextBob->RNGContext, contextBob->initiatorCachedSecretHash.pbxsecretID, 8);
	}

	if (contextBob->cachedSecret.rs1!=NULL) {
		contextBob->channelContext[0]->hmacFunction(contextBob->cachedSecret.rs1, contextBob->cachedSecret.rs1Length, (uint8_t *)"Responder", 9, 8, contextBob->responderCachedSecretHash.rs1ID);
	} else { /* we have no secret, generate a random */
		bctoolbox_rng_get(contextBob->RNGContext, contextBob->responderCachedSecretHash.rs1ID, 8);
	}

	if (contextBob->cachedSecret.rs2!=NULL) {
		contextBob->channelContext[0]->hmacFunction(contextBob->cachedSecret.rs2, contextBob->cachedSecret.rs2Length, (uint8_t *)"Responder", 9, 8, contextBob->responderCachedSecretHash.rs2ID);
	} else { /* we have no secret, generate a random */
		bctoolbox_rng_get(contextBob->RNGContext, contextBob->responderCachedSecretHash.rs2ID, 8);
	}

	if (contextBob->cachedSecret.auxsecret!=NULL) {
		contextBob->channelContext[0]->hmacFunction(contextBob->cachedSecret.auxsecret, contextBob->cachedSecret.auxsecretLength, contextBob->channelContext[0]->peerH[3], 32, 8, contextBob->channelContext[0]->responderAuxsecretID);
	} else { /* we have no secret, generate a random */
		bctoolbox_rng_get(contextBob->RNGContext, contextBob->channelContext[0]->responderAuxsecretID, 8);
	}

	if (contextBob->cachedSecret.pbxsecret!=NULL) {
		contextBob->channelContext[0]->hmacFunction(contextBob->cachedSecret.pbxsecret, contextBob->cachedSecret.pbxsecretLength, (uint8_t *)"Responder", 9, 8, contextBob->responderCachedSecretHash.pbxsecretID);
	} else { /* we have no secret, generate a random */
		bctoolbox_rng_get(contextBob->RNGContext, contextBob->responderCachedSecretHash.pbxsecretID, 8);
	}

	/* dump alice's packet on both sides */
	bzrtp_message ("\nAlice original Packet is \n");
	packetDump(alice_Hello, 1);
	bzrtp_message ("\nBob's parsed Alice Packet is \n");
	packetDump(bob_HelloFromAlice, 0);

	/* Create the DHPart2 packet (that we then may change to DHPart1 if we ended to be the responder) */
	alice_selfDHPart = bzrtp_createZrtpPacket(contextAlice, contextAlice->channelContext[0], MSGTYPE_DHPART2, &retval);
	retval += bzrtp_packetBuild(contextAlice, contextAlice->channelContext[0], alice_selfDHPart, 0); /* we don't care now about sequence number as we just need to build the message to be able to insert a hash of it into the commit packet */
	if (retval == 0) { /* ok, insert it in context as we need it to build the commit packet */
		contextAlice->channelContext[0]->selfPackets[DHPART_MESSAGE_STORE_ID] = alice_selfDHPart;
	} else {
		bzrtp_message ("Alice building DHPart packet returns %x\n", retval);
	}
	bob_selfDHPart = bzrtp_createZrtpPacket(contextBob, contextBob->channelContext[0], MSGTYPE_DHPART2, &retval);
	retval +=bzrtp_packetBuild(contextBob, contextBob->channelContext[0], bob_selfDHPart, 0); /* we don't care now about sequence number as we just need to build the message to be able to insert a hash of it into the commit packet */
	if (retval == 0) { /* ok, insert it in context as we need it to build the commit packet */
		contextBob->channelContext[0]->selfPackets[DHPART_MESSAGE_STORE_ID] = bob_selfDHPart;
	} else {
		bzrtp_message ("Bob building DHPart packet returns %x\n", retval);
	}
	bzrtp_message("Alice DHPart packet:\n");
	packetDump(alice_selfDHPart,0);
	bzrtp_message("Bob DHPart packet:\n");
	packetDump(bob_selfDHPart,0);

	/* respond to HELLO packet with an HelloACK - 1 create packets */
	alice_HelloACK = bzrtp_createZrtpPacket(contextAlice, contextAlice->channelContext[0], MSGTYPE_HELLOACK, &retval);
	retval += bzrtp_packetBuild(contextAlice, contextAlice->channelContext[0], alice_HelloACK, contextAlice->channelContext[0]->selfSequenceNumber);
	if (retval == 0) {
		contextAlice->channelContext[0]->selfSequenceNumber++;
	} else {
		bzrtp_message("Alice building HelloACK return %x\n", retval);
	}

	bob_HelloACK = bzrtp_createZrtpPacket(contextBob, contextBob->channelContext[0], MSGTYPE_HELLOACK, &retval);
	retval += bzrtp_packetBuild(contextBob, contextBob->channelContext[0], bob_HelloACK, contextBob->channelContext[0]->selfSequenceNumber);
	if (retval == 0) {
		contextBob->channelContext[0]->selfSequenceNumber++;
	} else {
		bzrtp_message("Bob building HelloACK return %x\n", retval);
	}

	/* exchange the HelloACK */
	alice_HelloACKFromBob = bzrtp_packetCheck(bob_HelloACK->packetString, bob_HelloACK->messageLength+16, contextAlice->channelContext[0]->peerSequenceNumber, &retval);
	retval +=  bzrtp_packetParser(contextAlice, contextAlice->channelContext[0], bob_HelloACK->packetString, bob_HelloACK->messageLength+16, alice_HelloACKFromBob);
	bzrtp_message ("Alice parsing Hello ACK returns %x\n", retval);
	if (retval==0) {
		contextAlice->channelContext[0]->peerSequenceNumber = alice_HelloACKFromBob->sequenceNumber;
	}

	bob_HelloACKFromAlice = bzrtp_packetCheck(alice_HelloACK->packetString, alice_HelloACK->messageLength+16, contextBob->channelContext[0]->peerSequenceNumber, &retval);
	retval +=  bzrtp_packetParser(contextBob, contextBob->channelContext[0], alice_HelloACK->packetString, alice_HelloACK->messageLength+16, bob_HelloACKFromAlice);
	bzrtp_message ("Bob parsing Hello ACK returns %x\n", retval);
	if (retval==0) {
		contextBob->channelContext[0]->peerSequenceNumber = bob_HelloACKFromAlice->sequenceNumber;
	}
	bzrtp_freeZrtpPacket(alice_HelloACK);
	bzrtp_freeZrtpPacket(bob_HelloACK);
	bzrtp_freeZrtpPacket(alice_HelloACKFromBob);
	bzrtp_freeZrtpPacket(bob_HelloACKFromAlice);


	/* now build the commit message (both Alice and Bob will send it, then use the mechanism of rfc section 4.2 to determine who will be the initiator)*/
	alice_Commit = bzrtp_createZrtpPacket(contextAlice, contextAlice->channelContext[0], MSGTYPE_COMMIT, &retval);
	retval += bzrtp_packetBuild(contextAlice, contextAlice->channelContext[0], alice_Commit, contextAlice->channelContext[0]->selfSequenceNumber);
	if (retval == 0) {
		contextAlice->channelContext[0]->selfSequenceNumber++;
		contextAlice->channelContext[0]->selfPackets[COMMIT_MESSAGE_STORE_ID] = alice_Commit;
	}
	bzrtp_message("Alice building Commit return %x\n", retval);

	bob_Commit = bzrtp_createZrtpPacket(contextBob, contextBob->channelContext[0], MSGTYPE_COMMIT, &retval);
	retval += bzrtp_packetBuild(contextBob, contextBob->channelContext[0], bob_Commit, contextBob->channelContext[0]->selfSequenceNumber);
	if (retval == 0) {
		contextBob->channelContext[0]->selfSequenceNumber++;
		contextBob->channelContext[0]->selfPackets[COMMIT_MESSAGE_STORE_ID] = bob_Commit;
	}
	bzrtp_message("Bob building Commit return %x\n", retval);


	/* and exchange the commits */
	bob_CommitFromAlice = bzrtp_packetCheck(alice_Commit->packetString, alice_Commit->messageLength+16, contextBob->channelContext[0]->peerSequenceNumber, &retval);
	retval += bzrtp_packetParser(contextBob, contextBob->channelContext[0], alice_Commit->packetString, alice_Commit->messageLength+16, bob_CommitFromAlice);
	bzrtp_message ("Bob parsing Commit returns %x\n", retval);
	if (retval==0) {
		/* update context with the information found in the packet */
		bzrtpCommitMessage_t *bob_CommitFromAlice_message = (bzrtpCommitMessage_t *)bob_CommitFromAlice->messageData;
		contextBob->channelContext[0]->peerSequenceNumber = bob_CommitFromAlice->sequenceNumber;
		memcpy(contextBob->channelContext[0]->peerH[2], bob_CommitFromAlice_message->H2, 32);
		contextBob->channelContext[0]->peerPackets[COMMIT_MESSAGE_STORE_ID] = bob_CommitFromAlice;
	}
	packetDump(bob_CommitFromAlice, 0);

	alice_CommitFromBob = bzrtp_packetCheck(bob_Commit->packetString, bob_Commit->messageLength+16, contextAlice->channelContext[0]->peerSequenceNumber, &retval);
	retval += bzrtp_packetParser(contextAlice, contextAlice->channelContext[0], bob_Commit->packetString, bob_Commit->messageLength+16, alice_CommitFromBob);
	bzrtp_message ("Alice parsing Commit returns %x\n", retval);
	if (retval==0) {
		/* update context with the information found in the packet */
		contextAlice->channelContext[0]->peerSequenceNumber = alice_CommitFromBob->sequenceNumber;
		/* Alice will be the initiator (commit contention not implemented in this test) so just discard bob's commit */
		/*bzrtpCommirMessage_t *alice_CommitFromBob_message = (bzrtpCommitMessage_t *)alice_CommitFromBob->messageData;
		memcpy(contextAlice->channelContext[0]->peerH[2], alice_CommitFromBob_message->H2, 32);
		contextAlice->channelContext[0]->peerPackets[COMMIT_MESSAGE_STORE_ID] = alice_CommitFromBob;*/
	}
	packetDump(alice_CommitFromBob, 0);
	bzrtp_freeZrtpPacket(alice_CommitFromBob);

	/* Now determine who shall be the initiator : rfc section 4.2 */
	/* select the one with the lowest value of hvi */
	/* for test purpose, we will set Alice as the initiator */
	contextBob->channelContext[0]->role = RESPONDER;

	/* Bob (responder) shall update his selected algo list to match Alice selection */
	/* no need to do this here as we have the same selection */

	/* Bob is the responder, rebuild his DHPart packet to be responder and not initiator : */
	/* as responder, bob must also swap his aux shared secret between responder and initiator as they are computed using the H3 and not a constant string */
	memcpy(tmpBuffer, contextBob->channelContext[0]->initiatorAuxsecretID, 8);
	memcpy(contextBob->channelContext[0]->initiatorAuxsecretID, contextBob->channelContext[0]->responderAuxsecretID, 8);
	memcpy(contextBob->channelContext[0]->responderAuxsecretID, tmpBuffer, 8);

	contextBob->channelContext[0]->selfPackets[DHPART_MESSAGE_STORE_ID]->messageType = MSGTYPE_DHPART1; /* we are now part 1*/
	bob_DHPart1 = (bzrtpDHPartMessage_t *)contextBob->channelContext[0]->selfPackets[DHPART_MESSAGE_STORE_ID]->messageData;
	/* change the shared secret ID to the responder one (we set them by default to the initiator's one) */
	memcpy(bob_DHPart1->rs1ID, contextBob->responderCachedSecretHash.rs1ID, 8);
	memcpy(bob_DHPart1->rs2ID, contextBob->responderCachedSecretHash.rs2ID, 8);
	memcpy(bob_DHPart1->auxsecretID, contextBob->channelContext[0]->responderAuxsecretID, 8);
	memcpy(bob_DHPart1->pbxsecretID, contextBob->responderCachedSecretHash.pbxsecretID, 8);

	retval +=bzrtp_packetBuild(contextBob, contextBob->channelContext[0], contextBob->channelContext[0]->selfPackets[DHPART_MESSAGE_STORE_ID],contextBob->channelContext[0]->selfSequenceNumber);
	if (retval == 0) {
		contextBob->channelContext[0]->selfSequenceNumber++;
	}
	bzrtp_message("Bob building DHPart1 return %x\n", retval);


	/* Alice parse bob's DHPart1 message */
	alice_DHPart1FromBob = bzrtp_packetCheck(contextBob->channelContext[0]->selfPackets[DHPART_MESSAGE_STORE_ID]->packetString, contextBob->channelContext[0]->selfPackets[DHPART_MESSAGE_STORE_ID]->messageLength+16, contextAlice->channelContext[0]->peerSequenceNumber, &retval);
	retval += bzrtp_packetParser(contextAlice, contextAlice->channelContext[0], contextBob->channelContext[0]->selfPackets[DHPART_MESSAGE_STORE_ID]->packetString, contextBob->channelContext[0]->selfPackets[DHPART_MESSAGE_STORE_ID]->messageLength+16, alice_DHPart1FromBob);
	bzrtp_message ("Alice parsing DHPart1 returns %x\n", retval);
	if (retval==0) {
		/* update context with the information found in the packet */
		contextAlice->channelContext[0]->peerSequenceNumber = alice_DHPart1FromBob->sequenceNumber;
		alice_DHPart1FromBob_message = (bzrtpDHPartMessage_t *)alice_DHPart1FromBob->messageData;
		memcpy(contextAlice->channelContext[0]->peerH[1], alice_DHPart1FromBob_message->H1, 32);
		contextAlice->channelContext[0]->peerPackets[DHPART_MESSAGE_STORE_ID] = alice_DHPart1FromBob;
	}
	packetDump(alice_DHPart1FromBob, 1);

	/* Now Alice may check which shared secret she expected and if they are valid in bob's DHPart1 */
	if (contextAlice->cachedSecret.rs1!=NULL) {
		if (memcmp(contextAlice->responderCachedSecretHash.rs1ID, alice_DHPart1FromBob_message->rs1ID,8) != 0) {
			bzrtp_message ("Alice found that requested shared secret rs1 ID differs!\n");
		} else {
			bzrtp_message("Alice validate rs1ID from bob DHPart1\n");
		}
	}
	if (contextAlice->cachedSecret.rs2!=NULL) {
		if (memcmp(contextAlice->responderCachedSecretHash.rs2ID, alice_DHPart1FromBob_message->rs2ID,8) != 0) {
			bzrtp_message ("Alice found that requested shared secret rs2 ID differs!\n");
		} else {
			bzrtp_message("Alice validate rs2ID from bob DHPart1\n");
		}
	}
	if (contextAlice->cachedSecret.auxsecret!=NULL) {
		if (memcmp(contextAlice->channelContext[0]->responderAuxsecretID, alice_DHPart1FromBob_message->auxsecretID,8) != 0) {
			bzrtp_message ("Alice found that requested shared secret aux secret ID differs!\n");
		} else {
			bzrtp_message("Alice validate aux secret ID from bob DHPart1\n");
		}
	}
	if (contextAlice->cachedSecret.pbxsecret!=NULL) {
		if (memcmp(contextAlice->responderCachedSecretHash.pbxsecretID, alice_DHPart1FromBob_message->pbxsecretID,8) != 0) {
			bzrtp_message ("Alice found that requested shared secret pbx secret ID differs!\n");
		} else {
			bzrtp_message("Alice validate pbxsecretID from bob DHPart1\n");
		}
	}

	/* Now Alice shall check that the PV from bob is not 1 or Prime-1 TODO*/
	/* Compute the shared DH secret */
	contextAlice->DHMContext->peer = (uint8_t *)malloc(contextAlice->channelContext[0]->keyAgreementLength*sizeof(uint8_t));
	memcpy (contextAlice->DHMContext->peer, alice_DHPart1FromBob_message->pv, contextAlice->channelContext[0]->keyAgreementLength);
	bctoolbox_DHMComputeSecret(contextAlice->DHMContext, (int (*)(void *, uint8_t *, size_t))bctoolbox_rng_get, (void *)contextAlice->RNGContext);

	/* So Alice send bob her DHPart2 message which is already prepared and stored (we just need to update the sequence number) */
	bzrtp_packetUpdateSequenceNumber(contextAlice->channelContext[0]->selfPackets[DHPART_MESSAGE_STORE_ID], contextAlice->channelContext[0]->selfSequenceNumber);
	contextAlice->channelContext[0]->selfSequenceNumber++;

	/* Bob parse Alice's DHPart2 message */
	bob_DHPart2FromAlice = bzrtp_packetCheck(contextAlice->channelContext[0]->selfPackets[DHPART_MESSAGE_STORE_ID]->packetString, contextAlice->channelContext[0]->selfPackets[DHPART_MESSAGE_STORE_ID]->messageLength+16, contextBob->channelContext[0]->peerSequenceNumber, &retval);
	bzrtp_message ("Bob checking DHPart2 returns %x\n", retval);
	retval += bzrtp_packetParser(contextBob, contextBob->channelContext[0], contextAlice->channelContext[0]->selfPackets[DHPART_MESSAGE_STORE_ID]->packetString, contextAlice->channelContext[0]->selfPackets[DHPART_MESSAGE_STORE_ID]->messageLength+16, bob_DHPart2FromAlice);
	bzrtp_message ("Bob parsing DHPart2 returns %x\n", retval);
	if (retval==0) {
		/* update context with the information found in the packet */
		contextBob->channelContext[0]->peerSequenceNumber = bob_DHPart2FromAlice->sequenceNumber;
		bob_DHPart2FromAlice_message = (bzrtpDHPartMessage_t *)bob_DHPart2FromAlice->messageData;
		memcpy(contextBob->channelContext[0]->peerH[1], bob_DHPart2FromAlice_message->H1, 32);
		contextBob->channelContext[0]->peerPackets[DHPART_MESSAGE_STORE_ID] = bob_DHPart2FromAlice;
	}
	packetDump(bob_DHPart2FromAlice, 0);

	/* Now Bob may check which shared secret she expected and if they are valid in bob's DHPart1 */
	if (contextBob->cachedSecret.rs1!=NULL) {
		if (memcmp(contextBob->initiatorCachedSecretHash.rs1ID, bob_DHPart2FromAlice_message->rs1ID,8) != 0) {
			bzrtp_message ("Bob found that requested shared secret rs1 ID differs!\n");
		} else {
			bzrtp_message("Bob validate rs1ID from Alice DHPart2\n");
		}
	}
	if (contextBob->cachedSecret.rs2!=NULL) {
		if (memcmp(contextBob->initiatorCachedSecretHash.rs2ID, bob_DHPart2FromAlice_message->rs2ID,8) != 0) {
			bzrtp_message ("Bob found that requested shared secret rs2 ID differs!\n");
		} else {
			bzrtp_message("Bob validate rs2ID from Alice DHPart2\n");
		}
	}
	if (contextBob->cachedSecret.auxsecret!=NULL) {
		if (memcmp(contextBob->channelContext[0]->initiatorAuxsecretID, bob_DHPart2FromAlice_message->auxsecretID,8) != 0) {
			bzrtp_message ("Bob found that requested shared secret aux secret ID differs!\n");
		} else {
			bzrtp_message("Bob validate aux secret ID from Alice DHPart2\n");
		}
	}
	if (contextBob->cachedSecret.pbxsecret!=NULL) {
		if (memcmp(contextBob->initiatorCachedSecretHash.pbxsecretID, bob_DHPart2FromAlice_message->pbxsecretID,8) != 0) {
			bzrtp_message ("Bob found that requested shared secret pbx secret ID differs!\n");
		} else {
			bzrtp_message("Bob validate pbxsecretID from Alice DHPart2\n");
		}
	}

	/* Now Bob shall check that the PV from Alice is not 1 or Prime-1 TODO*/
	/* Compute the shared DH secret */
	contextBob->DHMContext->peer = (uint8_t *)malloc(contextBob->channelContext[0]->keyAgreementLength*sizeof(uint8_t));
	memcpy (contextBob->DHMContext->peer, bob_DHPart2FromAlice_message->pv, contextBob->channelContext[0]->keyAgreementLength);
	bctoolbox_DHMComputeSecret(contextBob->DHMContext, (int (*)(void *, uint8_t *, size_t))bctoolbox_rng_get, (void *)contextAlice->RNGContext);


	/* JUST FOR TEST: check that the generated secrets are the same */
	secretLength = bob_DHPart2FromAlice->messageLength-84; /* length of generated secret is the same than public value */
	if (memcmp(contextBob->DHMContext->key, contextAlice->DHMContext->key, secretLength)==0) {
		bzrtp_message("Secret Key correctly exchanged \n");
		CU_PASS("Secret Key exchange OK");
	} else {
		CU_FAIL("Secret Key exchange failed");
		bzrtp_message("ERROR : secretKey exchange failed!!\n");
	}

	/* now compute the total_hash as in rfc section 4.4.1.4
	 * total_hash = hash(Hello of responder || Commit || DHPart1 || DHPart2)
	 */
	totalHashDataLength = bob_Hello->messageLength + alice_Commit->messageLength + contextBob->channelContext[0]->selfPackets[DHPART_MESSAGE_STORE_ID]->messageLength + alice_selfDHPart->messageLength;
	dataToHash = (uint8_t *)malloc(totalHashDataLength*sizeof(uint8_t));
	/* get all data from Alice */
	memcpy(dataToHash, contextAlice->channelContext[0]->peerPackets[HELLO_MESSAGE_STORE_ID]->packetString+ZRTP_PACKET_HEADER_LENGTH, contextAlice->channelContext[0]->peerPackets[HELLO_MESSAGE_STORE_ID]->messageLength);
	hashDataIndex += contextAlice->channelContext[0]->peerPackets[HELLO_MESSAGE_STORE_ID]->messageLength;
	memcpy(dataToHash+hashDataIndex, contextAlice->channelContext[0]->selfPackets[COMMIT_MESSAGE_STORE_ID]->packetString+ZRTP_PACKET_HEADER_LENGTH, contextAlice->channelContext[0]->selfPackets[COMMIT_MESSAGE_STORE_ID]->messageLength);
	hashDataIndex += contextAlice->channelContext[0]->selfPackets[COMMIT_MESSAGE_STORE_ID]->messageLength;
	memcpy(dataToHash+hashDataIndex, contextAlice->channelContext[0]->peerPackets[DHPART_MESSAGE_STORE_ID]->packetString+ZRTP_PACKET_HEADER_LENGTH, contextAlice->channelContext[0]->peerPackets[DHPART_MESSAGE_STORE_ID]->messageLength);
	hashDataIndex += contextAlice->channelContext[0]->peerPackets[DHPART_MESSAGE_STORE_ID]->messageLength;
	memcpy(dataToHash+hashDataIndex, contextAlice->channelContext[0]->selfPackets[DHPART_MESSAGE_STORE_ID]->packetString+ZRTP_PACKET_HEADER_LENGTH, contextAlice->channelContext[0]->selfPackets[DHPART_MESSAGE_STORE_ID]->messageLength);

	contextAlice->channelContext[0]->hashFunction(dataToHash, totalHashDataLength, 32, alice_totalHash);

	/* get all data from Bob */
	hashDataIndex = 0;
	memcpy(dataToHash, contextBob->channelContext[0]->selfPackets[HELLO_MESSAGE_STORE_ID]->packetString+ZRTP_PACKET_HEADER_LENGTH, contextBob->channelContext[0]->selfPackets[HELLO_MESSAGE_STORE_ID]->messageLength);
	hashDataIndex += contextBob->channelContext[0]->selfPackets[HELLO_MESSAGE_STORE_ID]->messageLength;
	memcpy(dataToHash+hashDataIndex, contextBob->channelContext[0]->peerPackets[COMMIT_MESSAGE_STORE_ID]->packetString+ZRTP_PACKET_HEADER_LENGTH, contextBob->channelContext[0]->peerPackets[COMMIT_MESSAGE_STORE_ID]->messageLength);
	hashDataIndex += contextBob->channelContext[0]->peerPackets[COMMIT_MESSAGE_STORE_ID]->messageLength;
	memcpy(dataToHash+hashDataIndex, contextBob->channelContext[0]->selfPackets[DHPART_MESSAGE_STORE_ID]->packetString+ZRTP_PACKET_HEADER_LENGTH, contextBob->channelContext[0]->selfPackets[DHPART_MESSAGE_STORE_ID]->messageLength);
	hashDataIndex += contextBob->channelContext[0]->selfPackets[DHPART_MESSAGE_STORE_ID]->messageLength;
	memcpy(dataToHash+hashDataIndex, contextBob->channelContext[0]->peerPackets[DHPART_MESSAGE_STORE_ID]->packetString+ZRTP_PACKET_HEADER_LENGTH, contextBob->channelContext[0]->peerPackets[DHPART_MESSAGE_STORE_ID]->messageLength);

	contextBob->channelContext[0]->hashFunction(dataToHash, totalHashDataLength, 32, bob_totalHash);
	if (memcmp(bob_totalHash, alice_totalHash, 32) == 0) {
		bzrtp_message("Got the same total hash\n");
		CU_PASS("Total Hash match");
	} else {
		bzrtp_message("AARGG!! total hash mismatch");
		CU_FAIL("Total Hash mismatch");
	}

	/* now compute s0 and KDF_context as in rfc section 4.4.1.4
		s0 = hash(counter || DHResult || "ZRTP-HMAC-KDF" || ZIDi || ZIDr || total_hash || len(s1) || s1 || len(s2) || s2 || len(s3) || s3)
		counter is a fixed 32 bits integer in big endian set to 1 : 0x00000001
	*/
	free(dataToHash);
	contextAlice->channelContext[0]->KDFContextLength = 24+32;/* actual depends on selected hash length*/
	contextAlice->channelContext[0]->KDFContext = (uint8_t *)malloc(contextAlice->channelContext[0]->KDFContextLength*sizeof(uint8_t));
	memcpy(contextAlice->channelContext[0]->KDFContext, contextAlice->selfZID, 12); /* ZIDi*/
	memcpy(contextAlice->channelContext[0]->KDFContext+12, contextAlice->peerZID, 12); /* ZIDr */
	memcpy(contextAlice->channelContext[0]->KDFContext+24, alice_totalHash, 32); /* total Hash*/

	/* get s1 from rs1 or rs2 */
	if (contextAlice->cachedSecret.rs1 != NULL) { /* if there is a s1 (already validated when received the DHpacket) */
		s1 = contextAlice->cachedSecret.rs1;
		s1Length = contextAlice->cachedSecret.rs1Length;
	} else if (contextAlice->cachedSecret.rs2 != NULL) { /* otherwise if there is a s2 (already validated when received the DHpacket) */
		s1 = contextAlice->cachedSecret.rs2;
		s1Length = contextAlice->cachedSecret.rs2Length;
	}

	/* s2 is the auxsecret */
	s2 = contextAlice->cachedSecret.auxsecret; /* this may be null if no match or no aux secret where found */
	s2Length = contextAlice->cachedSecret.auxsecretLength; /* this may be 0 if no match or no aux secret where found */

	/* s3 is the pbxsecret */
	s3 = contextAlice->cachedSecret.pbxsecret; /* this may be null if no match or no pbx secret where found */
	s3Length = contextAlice->cachedSecret.pbxsecretLength; /* this may be 0 if no match or no pbx secret where found */

	totalHashDataLength = 4+secretLength+13/*ZRTP-HMAC-KDF string*/ + 12 + 12 + 32 + 4 +s1Length + 4 +s2Length + 4 + s3Length; /* secret length was computed before as the length of DH secret data */

	dataToHash = (uint8_t *)malloc(totalHashDataLength*sizeof(uint8_t));
	dataToHash[0] = 0x00;
	dataToHash[1] = 0x00;
	dataToHash[2] = 0x00;
	dataToHash[3] = 0x01;
	hashDataIndex = 4;

	memcpy(dataToHash+hashDataIndex, contextAlice->DHMContext->key, secretLength);
	hashDataIndex += secretLength;
	memcpy(dataToHash+hashDataIndex, "ZRTP-HMAC-KDF", 13);
	hashDataIndex += 13;
	memcpy(dataToHash+hashDataIndex, contextAlice->channelContext[0]->KDFContext, contextAlice->channelContext[0]->KDFContextLength);
	hashDataIndex += 56;

	dataToHash[hashDataIndex++] = (uint8_t)((s1Length>>24)&0xFF);
	dataToHash[hashDataIndex++] = (uint8_t)((s1Length>>16)&0xFF);
	dataToHash[hashDataIndex++] = (uint8_t)((s1Length>>8)&0xFF);
	dataToHash[hashDataIndex++] = (uint8_t)(s1Length&0xFF);
	if (s1!=NULL) {
		memcpy(dataToHash+hashDataIndex, s1, s1Length);
		hashDataIndex += s1Length;
	}

	dataToHash[hashDataIndex++] = (uint8_t)((s2Length>>24)&0xFF);
	dataToHash[hashDataIndex++] = (uint8_t)((s2Length>>16)&0xFF);
	dataToHash[hashDataIndex++] = (uint8_t)((s2Length>>8)&0xFF);
	dataToHash[hashDataIndex++] = (uint8_t)(s2Length&0xFF);
	if (s2!=NULL) {
		memcpy(dataToHash+hashDataIndex, s2, s2Length);
		hashDataIndex += s2Length;
	}

	dataToHash[hashDataIndex++] = (uint8_t)((s3Length>>24)&0xFF);
	dataToHash[hashDataIndex++] = (uint8_t)((s3Length>>16)&0xFF);
	dataToHash[hashDataIndex++] = (uint8_t)((s3Length>>8)&0xFF);
	dataToHash[hashDataIndex++] = (uint8_t)(s3Length&0xFF);
	if (s3!=NULL) {
		memcpy(dataToHash+hashDataIndex, s3, s3Length);
		hashDataIndex += s3Length;
	}

	contextAlice->channelContext[0]->s0 = (uint8_t *)malloc(32*sizeof(uint8_t));
	contextAlice->channelContext[0]->hashFunction(dataToHash, totalHashDataLength, 32, contextAlice->channelContext[0]->s0);

	/* destroy all cached keys in context */
	if (contextAlice->cachedSecret.rs1!=NULL) {
		bzrtp_DestroyKey(contextAlice->cachedSecret.rs1, contextAlice->cachedSecret.rs1Length, contextAlice->RNGContext);
		free(contextAlice->cachedSecret.rs1);
		contextAlice->cachedSecret.rs1 = NULL;
	}
	if (contextAlice->cachedSecret.rs2!=NULL) {
		bzrtp_DestroyKey(contextAlice->cachedSecret.rs2, contextAlice->cachedSecret.rs2Length, contextAlice->RNGContext);
		free(contextAlice->cachedSecret.rs2);
		contextAlice->cachedSecret.rs2 = NULL;
	}
	if (contextAlice->cachedSecret.auxsecret!=NULL) {
		bzrtp_DestroyKey(contextAlice->cachedSecret.auxsecret, contextAlice->cachedSecret.auxsecretLength, contextAlice->RNGContext);
		free(contextAlice->cachedSecret.auxsecret);
		contextAlice->cachedSecret.auxsecret = NULL;
	}
	if (contextAlice->cachedSecret.pbxsecret!=NULL) {
		bzrtp_DestroyKey(contextAlice->cachedSecret.pbxsecret, contextAlice->cachedSecret.pbxsecretLength, contextAlice->RNGContext);
		free(contextAlice->cachedSecret.pbxsecret);
		contextAlice->cachedSecret.pbxsecret = NULL;
	}

	/*** Do the same for bob ***/
	/* get s1 from rs1 or rs2 */
	s1=NULL;
	s2=NULL;
	s3=NULL;
	contextBob->channelContext[0]->KDFContextLength = 24+32;/* actual depends on selected hash length*/
	contextBob->channelContext[0]->KDFContext = (uint8_t *)malloc(contextBob->channelContext[0]->KDFContextLength*sizeof(uint8_t));
	memcpy(contextBob->channelContext[0]->KDFContext, contextBob->peerZID, 12); /* ZIDi*/
	memcpy(contextBob->channelContext[0]->KDFContext+12, contextBob->selfZID, 12); /* ZIDr */
	memcpy(contextBob->channelContext[0]->KDFContext+24, bob_totalHash, 32); /* total Hash*/

	if (contextBob->cachedSecret.rs1 != NULL) { /* if there is a s1 (already validated when received the DHpacket) */
		s1 = contextBob->cachedSecret.rs1;
		s1Length = contextBob->cachedSecret.rs1Length;
	} else if (contextBob->cachedSecret.rs2 != NULL) { /* otherwise if there is a s2 (already validated when received the DHpacket) */
		s1 = contextBob->cachedSecret.rs2;
		s1Length = contextBob->cachedSecret.rs2Length;
	}

	/* s2 is the auxsecret */
	s2 = contextBob->cachedSecret.auxsecret; /* this may be null if no match or no aux secret where found */
	s2Length = contextBob->cachedSecret.auxsecretLength; /* this may be 0 if no match or no aux secret where found */

	/* s3 is the pbxsecret */
	s3 = contextBob->cachedSecret.pbxsecret; /* this may be null if no match or no pbx secret where found */
	s3Length = contextBob->cachedSecret.pbxsecretLength; /* this may be 0 if no match or no pbx secret where found */

	free(dataToHash);
	dataToHash = (uint8_t *)malloc(totalHashDataLength*sizeof(uint8_t));
	dataToHash[0] = 0x00;
	dataToHash[1] = 0x00;
	dataToHash[2] = 0x00;
	dataToHash[3] = 0x01;
	hashDataIndex = 4;

	memcpy(dataToHash+hashDataIndex, contextBob->DHMContext->key, secretLength);
	hashDataIndex += secretLength;
	memcpy(dataToHash+hashDataIndex, "ZRTP-HMAC-KDF", 13);
	hashDataIndex += 13;
	memcpy(dataToHash+hashDataIndex, contextBob->channelContext[0]->KDFContext, contextBob->channelContext[0]->KDFContextLength);
	hashDataIndex += 56;

	dataToHash[hashDataIndex++] = (uint8_t)((s1Length>>24)&0xFF);
	dataToHash[hashDataIndex++] = (uint8_t)((s1Length>>16)&0xFF);
	dataToHash[hashDataIndex++] = (uint8_t)((s1Length>>8)&0xFF);
	dataToHash[hashDataIndex++] = (uint8_t)(s1Length&0xFF);
	if (s1!=NULL) {
		memcpy(dataToHash+hashDataIndex, s1, s1Length);
		hashDataIndex += s1Length;
	}

	dataToHash[hashDataIndex++] = (uint8_t)((s2Length>>24)&0xFF);
	dataToHash[hashDataIndex++] = (uint8_t)((s2Length>>16)&0xFF);
	dataToHash[hashDataIndex++] = (uint8_t)((s2Length>>8)&0xFF);
	dataToHash[hashDataIndex++] = (uint8_t)(s2Length&0xFF);
	if (s2!=NULL) {
		memcpy(dataToHash+hashDataIndex, s2, s2Length);
		hashDataIndex += s2Length;
	}

	dataToHash[hashDataIndex++] = (uint8_t)((s3Length>>24)&0xFF);
	dataToHash[hashDataIndex++] = (uint8_t)((s3Length>>16)&0xFF);
	dataToHash[hashDataIndex++] = (uint8_t)((s3Length>>8)&0xFF);
	dataToHash[hashDataIndex++] = (uint8_t)(s3Length&0xFF);
	if (s3!=NULL) {
		memcpy(dataToHash+hashDataIndex, s3, s3Length);
		hashDataIndex += s3Length;
	}

	contextBob->channelContext[0]->s0 = (uint8_t *)malloc(32*sizeof(uint8_t));
	contextBob->channelContext[0]->hashFunction(dataToHash, totalHashDataLength, 32, contextBob->channelContext[0]->s0);

	free(dataToHash);

	/* destroy all cached keys in context */
	if (contextBob->cachedSecret.rs1!=NULL) {
		bzrtp_DestroyKey(contextBob->cachedSecret.rs1, contextBob->cachedSecret.rs1Length, contextBob->RNGContext);
		free(contextBob->cachedSecret.rs1);
		contextBob->cachedSecret.rs1 = NULL;
	}
	if (contextBob->cachedSecret.rs2!=NULL) {
		bzrtp_DestroyKey(contextBob->cachedSecret.rs2, contextBob->cachedSecret.rs2Length, contextBob->RNGContext);
		free(contextBob->cachedSecret.rs2);
		contextBob->cachedSecret.rs2 = NULL;
	}
	if (contextBob->cachedSecret.auxsecret!=NULL) {
		bzrtp_DestroyKey(contextBob->cachedSecret.auxsecret, contextBob->cachedSecret.auxsecretLength, contextBob->RNGContext);
		free(contextBob->cachedSecret.auxsecret);
		contextBob->cachedSecret.auxsecret = NULL;
	}
	if (contextBob->cachedSecret.pbxsecret!=NULL) {
		bzrtp_DestroyKey(contextBob->cachedSecret.pbxsecret, contextBob->cachedSecret.pbxsecretLength, contextBob->RNGContext);
		free(contextBob->cachedSecret.pbxsecret);
		contextBob->cachedSecret.pbxsecret = NULL;
	}


	/* DEBUG compare s0 */
	if (memcmp(contextBob->channelContext[0]->s0, contextAlice->channelContext[0]->s0, 32)==0) {
		bzrtp_message("Got the same s0\n");
		CU_PASS("s0 match");
	} else {
		bzrtp_message("ERROR s0 differs\n");
		CU_PASS("s0 mismatch");
	}

	/* now compute the ZRTPSession key : section 4.5.2
	 * ZRTPSess = KDF(s0, "ZRTP Session Key", KDF_Context, negotiated hash length)*/
	contextAlice->ZRTPSessLength=32; /* must be set to the length of negotiated hash */
	contextAlice->ZRTPSess = (uint8_t *)malloc(contextAlice->ZRTPSessLength*sizeof(uint8_t));
	retval = bzrtp_keyDerivationFunction(contextAlice->channelContext[0]->s0, contextAlice->channelContext[0]->hashLength,
		(uint8_t *)"ZRTP Session Key", 16,
		contextAlice->channelContext[0]->KDFContext, contextAlice->channelContext[0]->KDFContextLength, /* this one too depends on selected hash */
		contextAlice->channelContext[0]->hashLength,
		(void (*)(uint8_t *, uint8_t,  uint8_t *, uint32_t,  uint8_t,  uint8_t *))contextAlice->channelContext[0]->hmacFunction,
		contextAlice->ZRTPSess);

	contextBob->ZRTPSessLength=32; /* must be set to the length of negotiated hash */
	contextBob->ZRTPSess = (uint8_t *)malloc(contextBob->ZRTPSessLength*sizeof(uint8_t));
	retval = bzrtp_keyDerivationFunction(contextBob->channelContext[0]->s0, contextBob->channelContext[0]->hashLength,
		(uint8_t *)"ZRTP Session Key", 16,
		contextBob->channelContext[0]->KDFContext, contextBob->channelContext[0]->KDFContextLength, /* this one too depends on selected hash */
		contextBob->channelContext[0]->hashLength,
		(void (*)(uint8_t *, uint8_t,  uint8_t *, uint32_t,  uint8_t,  uint8_t *))contextBob->channelContext[0]->hmacFunction,
		contextBob->ZRTPSess);

	/* DEBUG compare ZRTPSess Key */
	if (memcmp(contextBob->ZRTPSess, contextAlice->ZRTPSess, 32)==0) {
		bzrtp_message("Got the same ZRTPSess\n");
		CU_PASS("ZRTPSess match");
	} else {
		bzrtp_message("ERROR ZRTPSess differs\n");
		CU_PASS("ZRTPSess mismatch");
	}


	/* compute the sas according to rfc section 4.5.2 sashash = KDF(s0, "SAS", KDF_Context, 256) */
	retval = bzrtp_keyDerivationFunction(contextAlice->channelContext[0]->s0, contextAlice->channelContext[0]->hashLength,
			(uint8_t *)"SAS", 3,
			contextAlice->channelContext[0]->KDFContext, contextAlice->channelContext[0]->KDFContextLength, /* this one too depends on selected hash */
			256/8, /* function gets L in bytes */
			(void (*)(uint8_t *, uint8_t,  uint8_t *, uint32_t,  uint8_t,  uint8_t *))contextAlice->channelContext[0]->hmacFunction,
			alice_sasHash);

	retval = bzrtp_keyDerivationFunction(contextBob->channelContext[0]->s0, contextBob->channelContext[0]->hashLength,
			(uint8_t *)"SAS", 3,
			contextBob->channelContext[0]->KDFContext, contextBob->channelContext[0]->KDFContextLength, /* this one too depends on selected hash */
			256/8, /* function gets L in bytes */
			(void (*)(uint8_t *, uint8_t,  uint8_t *, uint32_t,  uint8_t,  uint8_t *))contextBob->channelContext[0]->hmacFunction,
			bob_sasHash);

	/* DEBUG compare sasHash */
	if (memcmp(alice_sasHash, bob_sasHash, 32)==0) {
		bzrtp_message("Got the same SAS Hash\n");
		CU_PASS("SAS Hash match");
	} else {
		bzrtp_message("ERROR SAS Hash differs\n");
		CU_PASS("SAS Hash mismatch");
	}

	/* display SAS (we shall not do this now but after the confirm message exchanges) */
	sasValue = ((uint32_t)alice_sasHash[0]<<24) | ((uint32_t)alice_sasHash[1]<<16) | ((uint32_t)alice_sasHash[2]<<8) | ((uint32_t)(alice_sasHash[3]));
	contextAlice->channelContext[0]->sasFunction(sasValue, sas, 5);

	bzrtp_message("Alice SAS is %.4s\n", sas);

	sasValue = ((uint32_t)bob_sasHash[0]<<24) | ((uint32_t)bob_sasHash[1]<<16) | ((uint32_t)bob_sasHash[2]<<8) | ((uint32_t)(bob_sasHash[3]));
	contextBob->channelContext[0]->sasFunction(sasValue, sas, 5);

	bzrtp_message("Bob SAS is %.4s\n", sas);


	/* now derive the other keys (mackeyi, mackeyr, zrtpkeyi and zrtpkeyr, srtpkeys and salt) */
	contextAlice->channelContext[0]->mackeyi = (uint8_t *)malloc(contextAlice->channelContext[0]->hashLength*(sizeof(uint8_t)));
	contextAlice->channelContext[0]->mackeyr = (uint8_t *)malloc(contextAlice->channelContext[0]->hashLength*(sizeof(uint8_t)));
	contextAlice->channelContext[0]->zrtpkeyi = (uint8_t *)malloc(contextAlice->channelContext[0]->cipherKeyLength*(sizeof(uint8_t)));
	contextAlice->channelContext[0]->zrtpkeyr = (uint8_t *)malloc(contextAlice->channelContext[0]->cipherKeyLength*(sizeof(uint8_t)));
	contextBob->channelContext[0]->mackeyi = (uint8_t *)malloc(contextBob->channelContext[0]->hashLength*(sizeof(uint8_t)));
	contextBob->channelContext[0]->mackeyr = (uint8_t *)malloc(contextBob->channelContext[0]->hashLength*(sizeof(uint8_t)));
	contextBob->channelContext[0]->zrtpkeyi = (uint8_t *)malloc(contextBob->channelContext[0]->cipherKeyLength*(sizeof(uint8_t)));
	contextBob->channelContext[0]->zrtpkeyr = (uint8_t *)malloc(contextBob->channelContext[0]->cipherKeyLength*(sizeof(uint8_t)));

	/* Alice */
	retval = bzrtp_keyDerivationFunction(contextAlice->channelContext[0]->s0, contextAlice->channelContext[0]->hashLength, (uint8_t *)"Initiator HMAC key", 18, contextAlice->channelContext[0]->KDFContext, contextAlice->channelContext[0]->KDFContextLength, contextAlice->channelContext[0]->hashLength, (void (*)(uint8_t *, uint8_t,  uint8_t *, uint32_t,  uint8_t,  uint8_t *))contextAlice->channelContext[0]->hmacFunction, contextAlice->channelContext[0]->mackeyi);
	retval += bzrtp_keyDerivationFunction(contextAlice->channelContext[0]->s0, contextAlice->channelContext[0]->hashLength, (uint8_t *)"Responder HMAC key", 18, contextAlice->channelContext[0]->KDFContext, contextAlice->channelContext[0]->KDFContextLength, contextAlice->channelContext[0]->hashLength, (void (*)(uint8_t *, uint8_t,  uint8_t *, uint32_t,  uint8_t,  uint8_t *))contextAlice->channelContext[0]->hmacFunction, contextAlice->channelContext[0]->mackeyr);
	retval += bzrtp_keyDerivationFunction(contextAlice->channelContext[0]->s0, contextAlice->channelContext[0]->hashLength, (uint8_t *)"Initiator ZRTP key", 18, contextAlice->channelContext[0]->KDFContext, contextAlice->channelContext[0]->KDFContextLength, contextAlice->channelContext[0]->cipherKeyLength, (void (*)(uint8_t *, uint8_t,  uint8_t *, uint32_t,  uint8_t,  uint8_t *))contextAlice->channelContext[0]->hmacFunction, contextAlice->channelContext[0]->zrtpkeyi);
	retval += bzrtp_keyDerivationFunction(contextAlice->channelContext[0]->s0, contextAlice->channelContext[0]->hashLength, (uint8_t *)"Responder ZRTP key", 18, contextAlice->channelContext[0]->KDFContext, contextAlice->channelContext[0]->KDFContextLength, contextAlice->channelContext[0]->cipherKeyLength, (void (*)(uint8_t *, uint8_t,  uint8_t *, uint32_t,  uint8_t,  uint8_t *))contextAlice->channelContext[0]->hmacFunction, contextAlice->channelContext[0]->zrtpkeyr);

	/* Bob */
	retval = bzrtp_keyDerivationFunction(contextBob->channelContext[0]->s0, contextBob->channelContext[0]->hashLength, (uint8_t *)"Initiator HMAC key", 18, contextBob->channelContext[0]->KDFContext, contextBob->channelContext[0]->KDFContextLength, contextBob->channelContext[0]->hashLength, (void (*)(uint8_t *, uint8_t,  uint8_t *, uint32_t,  uint8_t,  uint8_t *))contextBob->channelContext[0]->hmacFunction, contextBob->channelContext[0]->mackeyi);
	retval += bzrtp_keyDerivationFunction(contextBob->channelContext[0]->s0, contextBob->channelContext[0]->hashLength, (uint8_t *)"Responder HMAC key", 18, contextBob->channelContext[0]->KDFContext, contextBob->channelContext[0]->KDFContextLength, contextBob->channelContext[0]->hashLength, (void (*)(uint8_t *, uint8_t,  uint8_t *, uint32_t,  uint8_t,  uint8_t *))contextBob->channelContext[0]->hmacFunction, contextBob->channelContext[0]->mackeyr);
	retval += bzrtp_keyDerivationFunction(contextBob->channelContext[0]->s0, contextBob->channelContext[0]->hashLength, (uint8_t *)"Initiator ZRTP key", 18, contextBob->channelContext[0]->KDFContext, contextBob->channelContext[0]->KDFContextLength, contextBob->channelContext[0]->cipherKeyLength, (void (*)(uint8_t *, uint8_t,  uint8_t *, uint32_t,  uint8_t,  uint8_t *))contextBob->channelContext[0]->hmacFunction, contextBob->channelContext[0]->zrtpkeyi);
	retval += bzrtp_keyDerivationFunction(contextBob->channelContext[0]->s0, contextBob->channelContext[0]->hashLength, (uint8_t *)"Responder ZRTP key", 18, contextBob->channelContext[0]->KDFContext, contextBob->channelContext[0]->KDFContextLength, contextBob->channelContext[0]->cipherKeyLength, (void (*)(uint8_t *, uint8_t,  uint8_t *, uint32_t,  uint8_t,  uint8_t *))contextBob->channelContext[0]->hmacFunction, contextBob->channelContext[0]->zrtpkeyr);


	/* DEBUG compare keys */
	if ((memcmp(contextAlice->channelContext[0]->mackeyi, contextBob->channelContext[0]->mackeyi, contextAlice->channelContext[0]->hashLength)==0) && (memcmp(contextAlice->channelContext[0]->mackeyr, contextBob->channelContext[0]->mackeyr, contextAlice->channelContext[0]->hashLength)==0) && (memcmp(contextAlice->channelContext[0]->zrtpkeyi, contextBob->channelContext[0]->zrtpkeyi, contextAlice->channelContext[0]->cipherKeyLength)==0) && (memcmp(contextAlice->channelContext[0]->zrtpkeyr, contextBob->channelContext[0]->zrtpkeyr, contextAlice->channelContext[0]->cipherKeyLength)==0)) {
		bzrtp_message("Got the same keys\n");
		CU_PASS("keys match");
	} else {
		bzrtp_message("ERROR keys differ\n");
		CU_PASS("Keys mismatch");
	}

	/* now Bob build the CONFIRM1 packet and send it to Alice */
	bob_Confirm1 = bzrtp_createZrtpPacket(contextBob, contextBob->channelContext[0], MSGTYPE_CONFIRM1, &retval);
	retval += bzrtp_packetBuild(contextBob, contextBob->channelContext[0], bob_Confirm1, contextBob->channelContext[0]->selfSequenceNumber);
	if (retval == 0) {
		contextBob->channelContext[0]->selfSequenceNumber++;
	}
	bzrtp_message("Bob building Confirm1 return %x\n", retval);

	alice_Confirm1FromBob = bzrtp_packetCheck(bob_Confirm1->packetString, bob_Confirm1->messageLength+16, contextAlice->channelContext[0]->peerSequenceNumber, &retval);
	retval += bzrtp_packetParser(contextAlice, contextAlice->channelContext[0], bob_Confirm1->packetString, bob_Confirm1->messageLength+16, alice_Confirm1FromBob);
	bzrtp_message ("Alice parsing confirm1 returns %x\n", retval);
	if (retval==0) {
		/* update context with the information found in the packet */
		contextAlice->channelContext[0]->peerSequenceNumber = alice_Confirm1FromBob->sequenceNumber;
		alice_Confirm1FromBob_message = (bzrtpConfirmMessage_t *)alice_Confirm1FromBob->messageData;
		memcpy(contextAlice->channelContext[0]->peerH[0], alice_Confirm1FromBob_message->H0, 32);
	}

	packetDump(bob_Confirm1,1);
	packetDump(alice_Confirm1FromBob,0);

	bzrtp_freeZrtpPacket(alice_Confirm1FromBob);
	bzrtp_freeZrtpPacket(bob_Confirm1);

	/* now Alice build the CONFIRM2 packet and send it to Bob */
	alice_Confirm2 = bzrtp_createZrtpPacket(contextAlice, contextAlice->channelContext[0], MSGTYPE_CONFIRM2, &retval);
	retval += bzrtp_packetBuild(contextAlice, contextAlice->channelContext[0], alice_Confirm2, contextAlice->channelContext[0]->selfSequenceNumber);
	if (retval == 0) {
		contextAlice->channelContext[0]->selfSequenceNumber++;
	}
	bzrtp_message("Alice building Confirm2 return %x\n", retval);

	bob_Confirm2FromAlice = bzrtp_packetCheck(alice_Confirm2->packetString, alice_Confirm2->messageLength+16, contextBob->channelContext[0]->peerSequenceNumber, &retval);
	retval += bzrtp_packetParser(contextBob, contextBob->channelContext[0], alice_Confirm2->packetString, alice_Confirm2->messageLength+16, bob_Confirm2FromAlice);
	bzrtp_message ("Bob parsing confirm2 returns %x\n", retval);
	if (retval==0) {
		/* update context with the information found in the packet */
		contextBob->channelContext[0]->peerSequenceNumber = bob_Confirm2FromAlice->sequenceNumber;
		bob_Confirm2FromAlice_message = (bzrtpConfirmMessage_t *)bob_Confirm2FromAlice->messageData;
		memcpy(contextBob->channelContext[0]->peerH[0], bob_Confirm2FromAlice_message->H0, 32);
		/* set bob's status to secure */
		contextBob->isSecure = 1;
	}

	packetDump(alice_Confirm2,1);
	packetDump(bob_Confirm2FromAlice,0);

	bzrtp_freeZrtpPacket(bob_Confirm2FromAlice);
	bzrtp_freeZrtpPacket(alice_Confirm2);

	/* Bob build the conf2Ack and send it to Alice */
	bob_Conf2ACK =  bzrtp_createZrtpPacket(contextBob, contextBob->channelContext[0], MSGTYPE_CONF2ACK, &retval);
	retval += bzrtp_packetBuild(contextBob, contextBob->channelContext[0], bob_Conf2ACK, contextBob->channelContext[0]->selfSequenceNumber);
	if (retval == 0) {
		contextBob->channelContext[0]->selfSequenceNumber++;
	}
	bzrtp_message("Bob building Conf2ACK return %x\n", retval);

	alice_Conf2ACKFromBob = bzrtp_packetCheck(bob_Conf2ACK->packetString, bob_Conf2ACK->messageLength+16, contextAlice->channelContext[0]->peerSequenceNumber, &retval);
	retval += bzrtp_packetParser(contextAlice, contextAlice->channelContext[0], bob_Conf2ACK->packetString, bob_Conf2ACK->messageLength+16, alice_Conf2ACKFromBob);
	bzrtp_message ("Alice parsing conf2ACK returns %x\n", retval);
	if (retval==0) {
		/* update context with the information found in the packet */
		contextAlice->channelContext[0]->peerSequenceNumber = alice_Conf2ACKFromBob->sequenceNumber;
		/* set Alice's status to secure */
		contextAlice->isSecure = 1;
	}

	bzrtp_freeZrtpPacket(bob_Conf2ACK);
	bzrtp_freeZrtpPacket(alice_Conf2ACKFromBob);

	dumpContext("Alice", contextAlice);
	dumpContext("Bob", contextBob);

	bzrtp_message("\n\n\n\n\n*************************************************************\n        SECOND CHANNEL\n**********************************************\n\n");
	/* Now create a second channel for Bob and Alice */
	retval = bzrtp_addChannel(contextAlice, 0x45678901);
	bzrtp_message("Add channel to Alice's context returns %d\n", retval);
	retval = bzrtp_addChannel(contextBob, 0x54321098);
	bzrtp_message("Add channel to Bob's context returns %d\n", retval);

	/* create hello packets for this channel */
	alice_Hello = bzrtp_createZrtpPacket(contextAlice, contextAlice->channelContext[1], MSGTYPE_HELLO, &retval);
	if (bzrtp_packetBuild(contextAlice, contextAlice->channelContext[1], alice_Hello, contextAlice->channelContext[1]->selfSequenceNumber) ==0) {
		contextAlice->channelContext[1]->selfSequenceNumber++;
		contextAlice->channelContext[1]->selfPackets[HELLO_MESSAGE_STORE_ID] = alice_Hello;
	}
	bob_Hello = bzrtp_createZrtpPacket(contextBob, contextBob->channelContext[1], MSGTYPE_HELLO, &retval);
	if (bzrtp_packetBuild(contextBob, contextBob->channelContext[1], bob_Hello, contextBob->channelContext[1]->selfSequenceNumber) ==0) {
		contextBob->channelContext[1]->selfSequenceNumber++;
		contextBob->channelContext[1]->selfPackets[HELLO_MESSAGE_STORE_ID] = bob_Hello;
	}

	/* now send Alice Hello's to Bob and vice-versa, so they parse them */
	alice_HelloFromBob = bzrtp_packetCheck(bob_Hello->packetString, bob_Hello->messageLength+16, contextAlice->channelContext[1]->peerSequenceNumber, &retval);
	retval +=  bzrtp_packetParser(contextAlice, contextAlice->channelContext[0], bob_Hello->packetString, bob_Hello->messageLength+16, alice_HelloFromBob);
	bzrtp_message ("Alice parsing returns %x\n", retval);
	if (retval==0) {
		bzrtpHelloMessage_t *alice_HelloFromBob_message;
		int i;
		uint8_t checkPeerSupportMultiChannel = 0;

		contextAlice->channelContext[1]->peerSequenceNumber = alice_HelloFromBob->sequenceNumber;
		/* save bob's Hello packet in Alice's context */
		contextAlice->channelContext[1]->peerPackets[HELLO_MESSAGE_STORE_ID] = alice_HelloFromBob;

		/* we are already secured (shall check isSecure==1), so we just need to check that peer Hello have the Mult in his key agreement list of supported algo */
		alice_HelloFromBob_message = (bzrtpHelloMessage_t *)alice_HelloFromBob->messageData;
		for (i=0; i<alice_HelloFromBob_message->kc; i++) {
			if (alice_HelloFromBob_message->supportedKeyAgreement[i] == ZRTP_KEYAGREEMENT_Mult) {
				checkPeerSupportMultiChannel = 1;
			}
		}

		/* ok multi channel is supported*/
		if (checkPeerSupportMultiChannel == 1) {
			bzrtp_message("Alice found that Bob supports multi channel\n");
			/* now set the choosen algos, they MUST be the same than main channel (channel 0) except for keyAgreement which is set to mult */
			contextAlice->channelContext[1]->hashAlgo = contextAlice->channelContext[0]->hashAlgo;
			contextAlice->channelContext[1]->hashLength = contextAlice->channelContext[0]->hashLength;
			contextAlice->channelContext[1]->cipherAlgo = contextAlice->channelContext[0]->cipherAlgo;
			contextAlice->channelContext[1]->cipherKeyLength = contextAlice->channelContext[0]->cipherKeyLength;
			contextAlice->channelContext[1]->authTagAlgo = contextAlice->channelContext[0]->authTagAlgo;
			contextAlice->channelContext[1]->sasAlgo = contextAlice->channelContext[0]->sasAlgo;
			contextAlice->channelContext[1]->keyAgreementAlgo = ZRTP_KEYAGREEMENT_Mult;
			contextAlice->channelContext[1]->keyAgreementLength = 0; /* no public values exchanged in Multi channel mode */

			updateCryptoFunctionPointers(contextAlice->channelContext[1]);
		} else {
			bzrtp_message("ERROR : Alice found that Bob doesn't support multi channel\n");
		}

	}

	bob_HelloFromAlice = bzrtp_packetCheck(alice_Hello->packetString, alice_Hello->messageLength+16, contextBob->channelContext[1]->peerSequenceNumber, &retval);
	retval +=  bzrtp_packetParser(contextBob, contextBob->channelContext[1], alice_Hello->packetString, alice_Hello->messageLength+16, bob_HelloFromAlice);
	bzrtp_message ("Bob parsing returns %x\n", retval);
	if (retval==0) {
		bzrtpHelloMessage_t *bob_HelloFromAlice_message;
		int i;
		uint8_t checkPeerSupportMultiChannel = 0;

		contextBob->channelContext[1]->peerSequenceNumber = bob_HelloFromAlice->sequenceNumber;
		/* save alice's Hello packet in bob's context */
		contextBob->channelContext[1]->peerPackets[HELLO_MESSAGE_STORE_ID] = bob_HelloFromAlice;

		/* we are already secured (shall check isSecure==1), so we just need to check that peer Hello have the Mult in his key agreement list of supported algo */
		bob_HelloFromAlice_message = (bzrtpHelloMessage_t *)bob_HelloFromAlice->messageData;
		for (i=0; i<bob_HelloFromAlice_message->kc; i++) {
			if (bob_HelloFromAlice_message->supportedKeyAgreement[i] == ZRTP_KEYAGREEMENT_Mult) {
				checkPeerSupportMultiChannel = 1;
			}
		}

		/* ok multi channel is supported*/
		if (checkPeerSupportMultiChannel == 1) {
			bzrtp_message("Bob found that Alice supports multi channel\n");
			/* now set the choosen algos, they MUST be the same than main channel (channel 0) except for keyAgreement which is set to mult */
			contextBob->channelContext[1]->hashAlgo = contextBob->channelContext[0]->hashAlgo;
			contextBob->channelContext[1]->hashLength = contextBob->channelContext[0]->hashLength;
			contextBob->channelContext[1]->cipherAlgo = contextBob->channelContext[0]->cipherAlgo;
			contextBob->channelContext[1]->cipherKeyLength = contextBob->channelContext[0]->cipherKeyLength;
			contextBob->channelContext[1]->authTagAlgo = contextBob->channelContext[0]->authTagAlgo;
			contextBob->channelContext[1]->sasAlgo = contextBob->channelContext[0]->sasAlgo;
			contextBob->channelContext[1]->keyAgreementAlgo = ZRTP_KEYAGREEMENT_Mult;
			contextBob->channelContext[1]->keyAgreementLength = 0; /* no public values exchanged in Multi channel mode */

			updateCryptoFunctionPointers(contextBob->channelContext[1]);
		} else {
			bzrtp_message("ERROR : Bob found that Alice doesn't support multi channel\n");
		}
	}

	/* update context with hello message information : H3  and compute initiator and responder's shared secret Hashs */
	alice_HelloFromBob_message = (bzrtpHelloMessage_t *)alice_HelloFromBob->messageData;
	memcpy(contextAlice->channelContext[1]->peerH[3], alice_HelloFromBob_message->H3, 32);
	bob_HelloFromAlice_message = (bzrtpHelloMessage_t *)bob_HelloFromAlice->messageData;
	memcpy(contextBob->channelContext[1]->peerH[3], bob_HelloFromAlice_message->H3, 32);


	/* here we shall exchange Hello ACK but it is just a test and was done already for channel 0, skip it as it is useless for the test */

	/* Bob will be the initiator, so compute a commit for him */
	bob_Commit = bzrtp_createZrtpPacket(contextBob, contextBob->channelContext[1], MSGTYPE_COMMIT, &retval);
	retval += bzrtp_packetBuild(contextBob, contextBob->channelContext[1], bob_Commit, contextBob->channelContext[1]->selfSequenceNumber);
	if (retval == 0) {
		contextBob->channelContext[1]->selfSequenceNumber++;
		contextBob->channelContext[1]->selfPackets[COMMIT_MESSAGE_STORE_ID] = bob_Commit;
	}
	bzrtp_message("Bob building Commit return %x\n", retval);


	/* and send it to Alice */
	alice_CommitFromBob = bzrtp_packetCheck(bob_Commit->packetString, bob_Commit->messageLength+16, contextAlice->channelContext[1]->peerSequenceNumber, &retval);
	retval += bzrtp_packetParser(contextAlice, contextAlice->channelContext[1], bob_Commit->packetString, bob_Commit->messageLength+16, alice_CommitFromBob);
	bzrtp_message ("Alice parsing Commit returns %x\n", retval);
	if (retval==0) {
		bzrtpCommitMessage_t *alice_CommitFromBob_message;

		/* update context with the information found in the packet */
		contextAlice->channelContext[1]->peerSequenceNumber = alice_CommitFromBob->sequenceNumber;
		/* Alice will be the initiator (commit contention not implemented in this test) so just discard bob's commit */
		alice_CommitFromBob_message = (bzrtpCommitMessage_t *)alice_CommitFromBob->messageData;
		memcpy(contextAlice->channelContext[1]->peerH[2], alice_CommitFromBob_message->H2, 32);
		contextAlice->channelContext[1]->peerPackets[COMMIT_MESSAGE_STORE_ID] = alice_CommitFromBob;
	}
	packetDump(alice_CommitFromBob, 0);

	/* for test purpose define Alice as the responder */
	contextAlice->channelContext[1]->role = RESPONDER;

	/* compute the total hash as in rfc section 4.4.3.2 total_hash = hash(Hello of responder || Commit) */
	totalHashDataLength = alice_Hello->messageLength + bob_Commit->messageLength;
	dataToHash = (uint8_t *)malloc(totalHashDataLength*sizeof(uint8_t));
	hashDataIndex = 0;

	/* get all data from Alice */
	memcpy(dataToHash, contextAlice->channelContext[1]->selfPackets[HELLO_MESSAGE_STORE_ID]->packetString+ZRTP_PACKET_HEADER_LENGTH, contextAlice->channelContext[1]->selfPackets[HELLO_MESSAGE_STORE_ID]->messageLength);
	hashDataIndex += contextAlice->channelContext[1]->selfPackets[HELLO_MESSAGE_STORE_ID]->messageLength;
	memcpy(dataToHash+hashDataIndex, contextAlice->channelContext[1]->peerPackets[COMMIT_MESSAGE_STORE_ID]->packetString+ZRTP_PACKET_HEADER_LENGTH, contextAlice->channelContext[1]->peerPackets[COMMIT_MESSAGE_STORE_ID]->messageLength);
	contextAlice->channelContext[1]->hashFunction(dataToHash, totalHashDataLength, 32, alice_totalHash);

	/* get all data from Bob */
	hashDataIndex = 0;
	memcpy(dataToHash, contextBob->channelContext[1]->peerPackets[HELLO_MESSAGE_STORE_ID]->packetString+ZRTP_PACKET_HEADER_LENGTH, contextBob->channelContext[1]->peerPackets[HELLO_MESSAGE_STORE_ID]->messageLength);
	hashDataIndex += contextBob->channelContext[1]->peerPackets[HELLO_MESSAGE_STORE_ID]->messageLength;
	memcpy(dataToHash+hashDataIndex, contextBob->channelContext[1]->selfPackets[COMMIT_MESSAGE_STORE_ID]->packetString+ZRTP_PACKET_HEADER_LENGTH, contextBob->channelContext[1]->selfPackets[COMMIT_MESSAGE_STORE_ID]->messageLength);

	contextBob->channelContext[1]->hashFunction(dataToHash, totalHashDataLength, 32, bob_totalHash);
	if (memcmp(bob_totalHash, alice_totalHash, 32) == 0) {
		bzrtp_message("Got the same total hash\n");
		CU_PASS("Total Hash match");
	} else {
		bzrtp_message("AARGG!! total hash mismatch");
		CU_FAIL("Total Hash mismatch");
	}

	free(dataToHash);


	/* compute the KDF Context as in rfc section 4.4.3.2 KDF_Context = (ZIDi || ZIDr || total_hash) */
	contextAlice->channelContext[1]->KDFContextLength = 24 + contextAlice->channelContext[1]->hashLength;
	contextAlice->channelContext[1]->KDFContext = (uint8_t *)malloc(contextAlice->channelContext[1]->KDFContextLength*sizeof(uint8_t));
	memcpy(contextAlice->channelContext[1]->KDFContext, contextAlice->peerZID, 12);
	memcpy(contextAlice->channelContext[1]->KDFContext+12, contextAlice->selfZID, 12);
	memcpy(contextAlice->channelContext[1]->KDFContext+24, alice_totalHash, contextAlice->channelContext[1]->hashLength);

	contextBob->channelContext[1]->KDFContextLength = 24 + contextBob->channelContext[1]->hashLength;
	contextBob->channelContext[1]->KDFContext = (uint8_t *)malloc(contextBob->channelContext[1]->KDFContextLength*sizeof(uint8_t));
	memcpy(contextBob->channelContext[1]->KDFContext, contextBob->selfZID, 12);
	memcpy(contextBob->channelContext[1]->KDFContext+12, contextBob->peerZID, 12);
	memcpy(contextBob->channelContext[1]->KDFContext+24, bob_totalHash, contextBob->channelContext[1]->hashLength);

	if (memcmp(contextBob->channelContext[1]->KDFContext, contextAlice->channelContext[1]->KDFContext, 56) == 0) {
		bzrtp_message("Got the same total KDF Context\n");
		CU_PASS("KDFContext match");
	} else {
		bzrtp_message("AARGG!! KDF Context mismatch");
		CU_FAIL("KDF Context mismatch");
	}

	/* compute s0 as in rfc section 4.4.3.2  s0 = KDF(ZRTPSess, "ZRTP MSK", KDF_Context, negotiated hash length) */
	contextBob->channelContext[1]->s0 = (uint8_t *)malloc(contextBob->channelContext[1]->hashLength*sizeof(uint8_t));
	contextAlice->channelContext[1]->s0 = (uint8_t *)malloc(contextAlice->channelContext[1]->hashLength*sizeof(uint8_t));
	retval = bzrtp_keyDerivationFunction(contextBob->ZRTPSess, contextBob->ZRTPSessLength,
		(uint8_t *)"ZRTP MSK", 8,
		contextBob->channelContext[1]->KDFContext, contextBob->channelContext[1]->KDFContextLength, /* this one too depends on selected hash */
		contextBob->channelContext[1]->hashLength,
		(void (*)(uint8_t *, uint8_t,  uint8_t *, uint32_t,  uint8_t,  uint8_t *))contextBob->channelContext[1]->hmacFunction,
		contextBob->channelContext[1]->s0);

	retval = bzrtp_keyDerivationFunction(contextAlice->ZRTPSess, contextAlice->ZRTPSessLength,
		(uint8_t *)"ZRTP MSK", 8,
		contextAlice->channelContext[1]->KDFContext, contextAlice->channelContext[1]->KDFContextLength, /* this one too depends on selected hash */
		contextAlice->channelContext[1]->hashLength,
		(void (*)(uint8_t *, uint8_t,  uint8_t *, uint32_t,  uint8_t,  uint8_t *))contextAlice->channelContext[1]->hmacFunction,
		contextAlice->channelContext[1]->s0);

	if (memcmp(contextBob->channelContext[1]->s0, contextAlice->channelContext[1]->s0, contextAlice->channelContext[1]->hashLength) == 0) {
		bzrtp_message("Got the same s0\n");
		CU_PASS("s0 match");
	} else {
		bzrtp_message("AARGG!! s0 mismatch");
		CU_FAIL("s0 mismatch");
	}


	/* the rest of key derivation is common to DH mode, no need to test it as it has been done before for channel 0 */
	/* we must anyway derive zrtp and mac key for initiator and responder in order to be able to build the confirm packets */
	contextAlice->channelContext[1]->mackeyi = (uint8_t *)malloc(contextAlice->channelContext[1]->hashLength*(sizeof(uint8_t)));
	contextAlice->channelContext[1]->mackeyr = (uint8_t *)malloc(contextAlice->channelContext[1]->hashLength*(sizeof(uint8_t)));
	contextAlice->channelContext[1]->zrtpkeyi = (uint8_t *)malloc(contextAlice->channelContext[1]->cipherKeyLength*(sizeof(uint8_t)));
	contextAlice->channelContext[1]->zrtpkeyr = (uint8_t *)malloc(contextAlice->channelContext[1]->cipherKeyLength*(sizeof(uint8_t)));
	contextBob->channelContext[1]->mackeyi = (uint8_t *)malloc(contextBob->channelContext[1]->hashLength*(sizeof(uint8_t)));
	contextBob->channelContext[1]->mackeyr = (uint8_t *)malloc(contextBob->channelContext[1]->hashLength*(sizeof(uint8_t)));
	contextBob->channelContext[1]->zrtpkeyi = (uint8_t *)malloc(contextBob->channelContext[1]->cipherKeyLength*(sizeof(uint8_t)));
	contextBob->channelContext[1]->zrtpkeyr = (uint8_t *)malloc(contextBob->channelContext[1]->cipherKeyLength*(sizeof(uint8_t)));

	/* Alice */
	retval = bzrtp_keyDerivationFunction(contextAlice->channelContext[1]->s0, contextAlice->channelContext[1]->hashLength, (uint8_t *)"Initiator HMAC key", 18, contextAlice->channelContext[1]->KDFContext, contextAlice->channelContext[1]->KDFContextLength, contextAlice->channelContext[1]->hashLength, (void (*)(uint8_t *, uint8_t,  uint8_t *, uint32_t,  uint8_t,  uint8_t *))contextAlice->channelContext[1]->hmacFunction, contextAlice->channelContext[1]->mackeyi);
	retval += bzrtp_keyDerivationFunction(contextAlice->channelContext[1]->s0, contextAlice->channelContext[1]->hashLength, (uint8_t *)"Responder HMAC key", 18, contextAlice->channelContext[1]->KDFContext, contextAlice->channelContext[1]->KDFContextLength, contextAlice->channelContext[1]->hashLength, (void (*)(uint8_t *, uint8_t,  uint8_t *, uint32_t,  uint8_t,  uint8_t *))contextAlice->channelContext[1]->hmacFunction, contextAlice->channelContext[1]->mackeyr);
	retval += bzrtp_keyDerivationFunction(contextAlice->channelContext[1]->s0, contextAlice->channelContext[1]->hashLength, (uint8_t *)"Initiator ZRTP key", 18, contextAlice->channelContext[1]->KDFContext, contextAlice->channelContext[1]->KDFContextLength, contextAlice->channelContext[1]->cipherKeyLength, (void (*)(uint8_t *, uint8_t,  uint8_t *, uint32_t,  uint8_t,  uint8_t *))contextAlice->channelContext[1]->hmacFunction, contextAlice->channelContext[1]->zrtpkeyi);
	retval += bzrtp_keyDerivationFunction(contextAlice->channelContext[1]->s0, contextAlice->channelContext[1]->hashLength, (uint8_t *)"Responder ZRTP key", 18, contextAlice->channelContext[1]->KDFContext, contextAlice->channelContext[1]->KDFContextLength, contextAlice->channelContext[1]->cipherKeyLength, (void (*)(uint8_t *, uint8_t,  uint8_t *, uint32_t,  uint8_t,  uint8_t *))contextAlice->channelContext[1]->hmacFunction, contextAlice->channelContext[1]->zrtpkeyr);

	/* Bob */
	retval = bzrtp_keyDerivationFunction(contextBob->channelContext[1]->s0, contextBob->channelContext[1]->hashLength, (uint8_t *)"Initiator HMAC key", 18, contextBob->channelContext[1]->KDFContext, contextBob->channelContext[1]->KDFContextLength, contextBob->channelContext[1]->hashLength, (void (*)(uint8_t *, uint8_t,  uint8_t *, uint32_t,  uint8_t,  uint8_t *))contextBob->channelContext[1]->hmacFunction, contextBob->channelContext[1]->mackeyi);
	retval += bzrtp_keyDerivationFunction(contextBob->channelContext[1]->s0, contextBob->channelContext[1]->hashLength, (uint8_t *)"Responder HMAC key", 18, contextBob->channelContext[1]->KDFContext, contextBob->channelContext[1]->KDFContextLength, contextBob->channelContext[1]->hashLength, (void (*)(uint8_t *, uint8_t,  uint8_t *, uint32_t,  uint8_t,  uint8_t *))contextBob->channelContext[1]->hmacFunction, contextBob->channelContext[1]->mackeyr);
	retval += bzrtp_keyDerivationFunction(contextBob->channelContext[1]->s0, contextBob->channelContext[1]->hashLength, (uint8_t *)"Initiator ZRTP key", 18, contextBob->channelContext[1]->KDFContext, contextBob->channelContext[1]->KDFContextLength, contextBob->channelContext[1]->cipherKeyLength, (void (*)(uint8_t *, uint8_t,  uint8_t *, uint32_t,  uint8_t,  uint8_t *))contextBob->channelContext[1]->hmacFunction, contextBob->channelContext[1]->zrtpkeyi);
	retval += bzrtp_keyDerivationFunction(contextBob->channelContext[1]->s0, contextBob->channelContext[1]->hashLength, (uint8_t *)"Responder ZRTP key", 18, contextBob->channelContext[1]->KDFContext, contextBob->channelContext[1]->KDFContextLength, contextBob->channelContext[1]->cipherKeyLength, (void (*)(uint8_t *, uint8_t,  uint8_t *, uint32_t,  uint8_t,  uint8_t *))contextBob->channelContext[1]->hmacFunction, contextBob->channelContext[1]->zrtpkeyr);

	/* DEBUG compare keys */
	if ((memcmp(contextAlice->channelContext[1]->mackeyi, contextBob->channelContext[1]->mackeyi, contextAlice->channelContext[1]->hashLength)==0) && (memcmp(contextAlice->channelContext[1]->mackeyr, contextBob->channelContext[1]->mackeyr, contextAlice->channelContext[1]->hashLength)==0) && (memcmp(contextAlice->channelContext[1]->zrtpkeyi, contextBob->channelContext[1]->zrtpkeyi, contextAlice->channelContext[1]->cipherKeyLength)==0) && (memcmp(contextAlice->channelContext[1]->zrtpkeyr, contextBob->channelContext[1]->zrtpkeyr, contextAlice->channelContext[1]->cipherKeyLength)==0)) {
		bzrtp_message("Got the same keys\n");
		CU_PASS("keys match");
	} else {
		bzrtp_message("ERROR keys differ\n");
		CU_PASS("Keys mismatch");
	}

	/* now Alice build a confirm1 packet */
	alice_Confirm1 = bzrtp_createZrtpPacket(contextAlice, contextAlice->channelContext[1], MSGTYPE_CONFIRM1, &retval);
	retval += bzrtp_packetBuild(contextAlice, contextAlice->channelContext[1], alice_Confirm1, contextAlice->channelContext[1]->selfSequenceNumber);
	if (retval == 0) {
		contextAlice->channelContext[1]->selfSequenceNumber++;
	}
	bzrtp_message("Alice building Confirm1 return %x\n", retval);

	bob_Confirm1FromAlice = bzrtp_packetCheck(alice_Confirm1->packetString, alice_Confirm1->messageLength+16, contextBob->channelContext[1]->peerSequenceNumber, &retval);
	retval += bzrtp_packetParser(contextBob, contextBob->channelContext[1], alice_Confirm1->packetString, alice_Confirm1->messageLength+16, bob_Confirm1FromAlice);
	bzrtp_message ("Bob parsing confirm1 returns %x\n", retval);
	if (retval==0) {
		/* update context with the information found in the packet */
		contextBob->channelContext[1]->peerSequenceNumber = bob_Confirm1FromAlice->sequenceNumber;
		bob_Confirm1FromAlice_message = (bzrtpConfirmMessage_t *)bob_Confirm1FromAlice->messageData;
		memcpy(contextBob->channelContext[1]->peerH[0], bob_Confirm1FromAlice_message->H0, 32);
	}

	packetDump(bob_Confirm1FromAlice,0);
	bzrtp_freeZrtpPacket(bob_Confirm1FromAlice);
	bzrtp_freeZrtpPacket(alice_Confirm1);

	/* now Bob build the CONFIRM2 packet and send it to Alice */
	bob_Confirm2 = bzrtp_createZrtpPacket(contextBob, contextBob->channelContext[1], MSGTYPE_CONFIRM2, &retval);
	retval += bzrtp_packetBuild(contextBob, contextBob->channelContext[1], bob_Confirm2, contextBob->channelContext[1]->selfSequenceNumber);
	if (retval == 0) {
		contextBob->channelContext[1]->selfSequenceNumber++;
	}
	bzrtp_message("Bob building Confirm2 return %x\n", retval);
	alice_Confirm2FromBob = bzrtp_packetCheck(bob_Confirm2->packetString, bob_Confirm2->messageLength+16, contextAlice->channelContext[1]->peerSequenceNumber, &retval);
	retval += bzrtp_packetParser(contextAlice, contextAlice->channelContext[1], bob_Confirm2->packetString, bob_Confirm2->messageLength+16, alice_Confirm2FromBob);
	bzrtp_message ("Alice parsing confirm2 returns %x\n", retval);
	if (retval==0) {
		/* update context with the information found in the packet */
		contextAlice->channelContext[1]->peerSequenceNumber = alice_Confirm2FromBob->sequenceNumber;
		alice_Confirm2FromBob_message = (bzrtpConfirmMessage_t *)alice_Confirm2FromBob->messageData;
		memcpy(contextAlice->channelContext[1]->peerH[0], alice_Confirm2FromBob_message->H0, 32);
	}

	packetDump(alice_Confirm2FromBob,0);
	bzrtp_freeZrtpPacket(alice_Confirm2FromBob);
	bzrtp_freeZrtpPacket(bob_Confirm2);

	/* Alice build the conf2Ack and send it to Bob */
	alice_Conf2ACK =  bzrtp_createZrtpPacket(contextAlice, contextAlice->channelContext[1], MSGTYPE_CONF2ACK, &retval);
	retval += bzrtp_packetBuild(contextAlice, contextAlice->channelContext[1], alice_Conf2ACK, contextAlice->channelContext[1]->selfSequenceNumber);
	if (retval == 0) {
		contextAlice->channelContext[1]->selfSequenceNumber++;
	}
	bzrtp_message("Alice building Conf2ACK return %x\n", retval);

	bob_Conf2ACKFromAlice = bzrtp_packetCheck(alice_Conf2ACK->packetString, alice_Conf2ACK->messageLength+16, contextBob->channelContext[1]->peerSequenceNumber, &retval);
	retval += bzrtp_packetParser(contextBob, contextBob->channelContext[1], alice_Conf2ACK->packetString, alice_Conf2ACK->messageLength+16, bob_Conf2ACKFromAlice);
	bzrtp_message ("Bob parsing conf2ACK returns %x\n", retval);
	if (retval==0) {
		/* update context with the information found in the packet */
		contextBob->channelContext[1]->peerSequenceNumber = bob_Conf2ACKFromAlice->sequenceNumber;
	}


	bzrtp_freeZrtpPacket(alice_Conf2ACK);
	bzrtp_freeZrtpPacket(bob_Conf2ACKFromAlice);





/*
	dumpContext("\nAlice", contextAlice);
	dumpContext("\nBob", contextBob);
*/
	bzrtp_message("Destroy the contexts\n");
	/* destroy the context */
	bzrtp_destroyBzrtpContext(contextAlice, 0x45678901);
	bzrtp_destroyBzrtpContext(contextBob, 0x54321098);
	bzrtp_message("Destroy the contexts last channel\n");
	bzrtp_destroyBzrtpContext(contextBob, 0x87654321);
	bzrtp_destroyBzrtpContext(contextAlice, 0x12345678);

}
