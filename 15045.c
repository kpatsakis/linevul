void qeth_schedule_recovery(struct qeth_card *card)
{
	QETH_CARD_TEXT(card, 2, "startrec");
	if (qeth_set_thread_start_bit(card, QETH_RECOVER_THREAD) == 0)
		schedule_work(&card->kernel_thread_starter);
}
