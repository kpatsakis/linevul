const base::FilePath& DriveFsHost::GetMountPath() const {
  DCHECK(IsMounted());
  return mount_state_->mount_path();
}
