Job::~Job() {
  DCHECK(!pending_dns_);
  DCHECK(callback_.is_null());
  DCHECK(!bindings_);
}
