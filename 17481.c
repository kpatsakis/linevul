static void DoHTCSendPktsTest(struct ar6_softc *ar, int MapNo, HTC_ENDPOINT_ID eid, struct sk_buff *dupskb)
{
    struct ar_cookie *cookie;
    struct ar_cookie *cookieArray[HTC_TEST_DUPLICATE];
    struct sk_buff   *new_skb;
    int    i;
    int    pkts = 0;
    struct htc_packet_queue pktQueue;
    EPPING_HEADER    *eppingHdr;

    eppingHdr = A_NETBUF_DATA(dupskb);

    if (eppingHdr->Cmd_h == EPPING_CMD_NO_ECHO) {
        /* skip test if this is already a tx perf test */
        return;
    }

    for (i = 0; i < HTC_TEST_DUPLICATE; i++,pkts++) {
        AR6000_SPIN_LOCK(&ar->arLock, 0);
        cookie = ar6000_alloc_cookie(ar);
        if (cookie != NULL) {
            ar->arTxPending[eid]++;
            ar->arTotalTxDataPending++;
        }

        AR6000_SPIN_UNLOCK(&ar->arLock, 0);

        if (NULL == cookie) {
            break;
        }

        new_skb = A_NETBUF_ALLOC(A_NETBUF_LEN(dupskb));

        if (new_skb == NULL) {
            AR6000_SPIN_LOCK(&ar->arLock, 0);
            ar6000_free_cookie(ar,cookie);
            AR6000_SPIN_UNLOCK(&ar->arLock, 0);
            break;
        }

        A_NETBUF_PUT_DATA(new_skb, A_NETBUF_DATA(dupskb), A_NETBUF_LEN(dupskb));
        cookie->arc_bp[0] = (unsigned long)new_skb;
        cookie->arc_bp[1] = MapNo;
        SET_HTC_PACKET_INFO_TX(&cookie->HtcPkt,
                               cookie,
                               A_NETBUF_DATA(new_skb),
                               A_NETBUF_LEN(new_skb),
                               eid,
                               AR6K_DATA_PKT_TAG);

        cookieArray[i] = cookie;

        {
            EPPING_HEADER *pHdr = (EPPING_HEADER *)A_NETBUF_DATA(new_skb);
            pHdr->Cmd_h = EPPING_CMD_NO_ECHO;  /* do not echo the packet */
        }
    }

    if (pkts == 0) {
        return;
    }

    INIT_HTC_PACKET_QUEUE(&pktQueue);

    for (i = 0; i < pkts; i++) {
        HTC_PACKET_ENQUEUE(&pktQueue,&cookieArray[i]->HtcPkt);
    }

    HTCSendPktsMultiple(ar->arHtcTarget, &pktQueue);

}
