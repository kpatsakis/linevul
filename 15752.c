void PostAsyncTask(SkiaOutputSurfaceDependency* dependency,
                   const base::RepeatingCallback<void(Args...)>& callback,
                   Args... args) {
  dependency->PostTaskToClientThread(base::BindOnce(callback, args...));
}
