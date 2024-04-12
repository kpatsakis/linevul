void qeth_tx_timeout(struct net_device *dev)
{
	struct qeth_card *card;

	card = dev->ml_priv;
	QETH_CARD_TEXT(card, 4, "txtimeo");
	card->stats.tx_errors++;
	qeth_schedule_recovery(card);
}
