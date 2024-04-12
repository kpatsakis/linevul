void ApiTestEnvironment::RunPromisesAgain() {
  env()->isolate()->RunMicrotasks();
  base::MessageLoop::current()->PostTask(
      FROM_HERE, base::Bind(&ApiTestEnvironment::RunPromisesAgain,
                            base::Unretained(this)));
}
