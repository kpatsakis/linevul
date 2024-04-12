ImageBitmapFactories& WorkerGlobalScopeImageBitmapFactories::fromInternal(WorkerGlobalScope& object)
{
    WorkerGlobalScopeImageBitmapFactories* supplement = static_cast<WorkerGlobalScopeImageBitmapFactories*>(WillBeHeapSupplement<WorkerGlobalScope>::from(object, ImageBitmapFactories::supplementName()));
    if (!supplement) {
        supplement = new WorkerGlobalScopeImageBitmapFactories();
        WillBeHeapSupplement<WorkerGlobalScope>::provideTo(object, ImageBitmapFactories::supplementName(), adoptPtrWillBeNoop(supplement));
    }
    return *supplement;
}
