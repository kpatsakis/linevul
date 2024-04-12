static int unpriv_assign_nic(struct lxc_netdev *netdev, pid_t pid)
{
	pid_t child;
	int bytes, pipefd[2];
	char *token, *saveptr = NULL;
	char buffer[MAX_BUFFER_SIZE];
	char netdev_link[IFNAMSIZ+1];

	if (netdev->type != LXC_NET_VETH) {
		ERROR("nic type %d not support for unprivileged use",
			netdev->type);
		return -1;
	}

	if(pipe(pipefd) < 0) {
		SYSERROR("pipe failed");
		return -1;
	}

	if ((child = fork()) < 0) {
		SYSERROR("fork");
		close(pipefd[0]);
		close(pipefd[1]);
		return -1;
	}

	if (child == 0) { // child
		/* close the read-end of the pipe */
		close(pipefd[0]);
		/* redirect the stdout to write-end of the pipe */
		dup2(pipefd[1], STDOUT_FILENO);
		/* close the write-end of the pipe */
		close(pipefd[1]);

		char pidstr[20];
		if (netdev->link) {
			strncpy(netdev_link, netdev->link, IFNAMSIZ);
		} else {
			strncpy(netdev_link, "none", IFNAMSIZ);
		}
		char *args[] = {LXC_USERNIC_PATH, pidstr, "veth", netdev_link, netdev->name, NULL };
		snprintf(pidstr, 19, "%lu", (unsigned long) pid);
		pidstr[19] = '\0';
		execvp(args[0], args);
		SYSERROR("execvp lxc-user-nic");
		exit(1);
	}

	/* close the write-end of the pipe */
	close(pipefd[1]);

	bytes = read(pipefd[0], &buffer, MAX_BUFFER_SIZE);
	if (bytes < 0) {
		SYSERROR("read failed");
	}
	buffer[bytes - 1] = '\0';

	if (wait_for_pid(child) != 0) {
		close(pipefd[0]);
		return -1;
	}

	/* close the read-end of the pipe */
	close(pipefd[0]);

	/* fill netdev->name field */
	token = strtok_r(buffer, ":", &saveptr);
	if (!token)
		return -1;
	netdev->name = malloc(IFNAMSIZ+1);
	if (!netdev->name) {
		ERROR("Out of memory");
		return -1;
	}
	memset(netdev->name, 0, IFNAMSIZ+1);
	strncpy(netdev->name, token, IFNAMSIZ);

	/* fill netdev->veth_attr.pair field */
	token = strtok_r(NULL, ":", &saveptr);
	if (!token)
		return -1;
	netdev->priv.veth_attr.pair = strdup(token);
	if (!netdev->priv.veth_attr.pair) {
		ERROR("Out of memory");
		return -1;
	}

	return 0;
}
