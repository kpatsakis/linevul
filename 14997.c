static void nfs4_set_sequence_privileged(struct nfs4_sequence_args *args)
{
	args->sa_privileged = 1;
}
