BrowserRenderProcessHost::BrowserRenderProcessHost(Profile* profile)
    : RenderProcessHost(profile),
      visible_widgets_(0),
      backgrounded_(true),
      ALLOW_THIS_IN_INITIALIZER_LIST(cached_dibs_cleaner_(
            base::TimeDelta::FromSeconds(5),
            this, &BrowserRenderProcessHost::ClearTransportDIBCache)),
      accessibility_enabled_(false),
      is_initialized_(false) {
  widget_helper_ = new RenderWidgetHelper();

  ChildProcessSecurityPolicy::GetInstance()->Add(id());

  ChildProcessSecurityPolicy::GetInstance()->GrantPermissionsForFile(
      id(), profile->GetPath().Append(
          fileapi::SandboxMountPointProvider::kNewFileSystemDirectory),
      base::PLATFORM_FILE_OPEN |
      base::PLATFORM_FILE_CREATE |
      base::PLATFORM_FILE_OPEN_ALWAYS |
      base::PLATFORM_FILE_CREATE_ALWAYS |
      base::PLATFORM_FILE_OPEN_TRUNCATED |
      base::PLATFORM_FILE_READ |
      base::PLATFORM_FILE_WRITE |
      base::PLATFORM_FILE_EXCLUSIVE_READ |
      base::PLATFORM_FILE_EXCLUSIVE_WRITE |
      base::PLATFORM_FILE_ASYNC |
      base::PLATFORM_FILE_WRITE_ATTRIBUTES |
      base::PLATFORM_FILE_ENUMERATE);
  ChildProcessSecurityPolicy::GetInstance()->GrantPermissionsForFile(
      id(), profile->GetPath().Append(
          fileapi::SandboxMountPointProvider::kOldFileSystemDirectory),
      base::PLATFORM_FILE_READ | base::PLATFORM_FILE_WRITE |
      base::PLATFORM_FILE_WRITE_ATTRIBUTES | base::PLATFORM_FILE_ENUMERATE);
  ChildProcessSecurityPolicy::GetInstance()->GrantPermissionsForFile(
      id(), profile->GetPath().Append(
          fileapi::SandboxMountPointProvider::kRenamedOldFileSystemDirectory),
      base::PLATFORM_FILE_CREATE | base::PLATFORM_FILE_CREATE_ALWAYS |
      base::PLATFORM_FILE_WRITE);

}
