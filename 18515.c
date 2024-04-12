void ProfilingService::OnStart() {
  ref_factory_.reset(new service_manager::ServiceContextRefFactory(base::Bind(
      &ProfilingService::MaybeRequestQuitDelayed, base::Unretained(this))));
  registry_.AddInterface(
      base::Bind(&ProfilingService::OnProfilingServiceRequest,
                 base::Unretained(this), ref_factory_.get()));
}
