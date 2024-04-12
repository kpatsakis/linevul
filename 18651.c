int getJobAdExitedBySignal(ClassAd *jad, int &exited_by_signal)
{
	if( ! jad->LookupInteger(ATTR_ON_EXIT_BY_SIGNAL, exited_by_signal) ) {
		return FALSE;
	}

	return TRUE;
}
