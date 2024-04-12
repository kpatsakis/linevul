void rpc_show_tasks(void)
{
	struct rpc_clnt *clnt;
	struct rpc_task *task;
	int header = 0;

	spin_lock(&rpc_client_lock);
	list_for_each_entry(clnt, &all_clients, cl_clients) {
		spin_lock(&clnt->cl_lock);
		list_for_each_entry(task, &clnt->cl_tasks, tk_task) {
			if (!header) {
				rpc_show_header();
				header++;
			}
			rpc_show_task(clnt, task);
		}
		spin_unlock(&clnt->cl_lock);
	}
	spin_unlock(&rpc_client_lock);
}
