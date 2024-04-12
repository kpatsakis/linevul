GaiaCookieManagerService::~GaiaCookieManagerService() {
  CancelAll();
  DCHECK(requests_.empty());
}
