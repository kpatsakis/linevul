base::Closure RunLoop::QuitClosure() {

  return base::Bind(&ProxyToTaskRunner, origin_task_runner_,
                    base::Bind(&RunLoop::Quit, weak_factory_.GetWeakPtr()));
}
