XRecordFreeState(XRecordState *state)
{
    int i;

    for(i=0; i<state->nclients; i++) {
	if (state->client_info[i]->ranges) {
	    if (state->client_info[i]->ranges[0])
		Xfree(state->client_info[i]->ranges[0]);
	    Xfree(state->client_info[i]->ranges);
	}
    }
    if (state->client_info) {
	if (state->client_info[0])
	    Xfree(state->client_info[0]);
	Xfree(state->client_info);
    }
    Xfree(state);
}
