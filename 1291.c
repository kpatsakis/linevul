void ChildProcessSecurityPolicyImpl::RegisterWebSafeScheme(
    const std::string& scheme) {
  base::AutoLock lock(lock_);
  DCHECK_EQ(0U, schemes_okay_to_request_in_any_process_.count(scheme))
      << "Add schemes at most once.";
  DCHECK_EQ(0U, pseudo_schemes_.count(scheme))
      << "Web-safe implies not pseudo.";

  schemes_okay_to_request_in_any_process_.insert(scheme);
  schemes_okay_to_commit_in_any_process_.insert(scheme);
}
