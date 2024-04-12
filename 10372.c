static bool nfsd4_compound_in_session(struct nfsd4_session *session, struct nfs4_sessionid *sid)
{
	if (!session)
		return 0;
	return !memcmp(sid, &session->se_sessionid, sizeof(*sid));
}
