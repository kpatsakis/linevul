sig_chld(int signo)
{
    int p_stat;
    pid_t pid;

#ifdef HAVE_WAITPID
    while ((pid = waitpid(-1, &p_stat, WNOHANG)) > 0)
#elif HAVE_WAIT3
    while ((pid = wait3(&p_stat, WNOHANG, NULL)) > 0)
#else
    if ((pid = wait(&p_stat)) > 0)
#endif
    {
	DownloadList *d;

	if (WIFEXITED(p_stat)) {
	    for (d = FirstDL; d != NULL; d = d->next) {
		if (d->pid == pid) {
		    d->err = WEXITSTATUS(p_stat);
		    break;
		}
	    }
	}
    }
    mySignal(SIGCHLD, sig_chld);
    return;
}
