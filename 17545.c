void CoordinatorImpl::RequestPrivateMemoryFootprint(
    base::ProcessId pid,
    RequestPrivateMemoryFootprintCallback callback) {
  auto adapter = [](RequestPrivateMemoryFootprintCallback callback,
                    bool success, uint64_t,
                    mojom::GlobalMemoryDumpPtr global_memory_dump) {
    std::move(callback).Run(success, std::move(global_memory_dump));
  };

  QueuedRequest::Args args(
      base::trace_event::MemoryDumpType::SUMMARY_ONLY,
      base::trace_event::MemoryDumpLevelOfDetail::BACKGROUND, {},
      false /* add_to_trace */, pid, /*memory_footprint_only=*/true);
  RequestGlobalMemoryDumpInternal(args,
                                  base::BindOnce(adapter, std::move(callback)));
}
