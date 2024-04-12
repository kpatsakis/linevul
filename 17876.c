DriveFsHost::DriveFsHost(const base::FilePath& profile_path,
                         DriveFsHost::Delegate* delegate)
    : profile_path_(profile_path),
      delegate_(delegate) {
  chromeos::disks::DiskMountManager::GetInstance()->AddObserver(this);
}
