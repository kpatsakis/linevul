void Compositor::DidFailToInitializeLayerTreeFrameSink() {
  task_runner_->PostTask(
      FROM_HERE,
      base::BindOnce(&Compositor::RequestNewLayerTreeFrameSink,
                     context_creation_weak_ptr_factory_.GetWeakPtr()));
}
