FileTransfer::Continue()
{
	int result = TRUE;	// return TRUE if there currently is no thread

	if (ActiveTransferTid != -1 ) {
		ASSERT( daemonCore );
		result = daemonCore->Continue_Thread(ActiveTransferTid);
	}

	return result;
}
