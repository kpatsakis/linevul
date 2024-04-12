MultibufferDataSource::ReadOperation::~ReadOperation() {
  DCHECK(callback_.is_null());
}
