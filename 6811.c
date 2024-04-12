MojoResult MojoPlatformHandleToScopedPlatformHandle(
    const MojoPlatformHandle* platform_handle,
    ScopedPlatformHandle* out_handle) {
  if (platform_handle->struct_size != sizeof(MojoPlatformHandle))
    return MOJO_RESULT_INVALID_ARGUMENT;

  if (platform_handle->type == MOJO_PLATFORM_HANDLE_TYPE_INVALID) {
    out_handle->reset();
    return MOJO_RESULT_OK;
  }

  PlatformHandle handle;
  switch (platform_handle->type) {
#if defined(OS_FUCHSIA)
    case MOJO_PLATFORM_HANDLE_TYPE_FUCHSIA_HANDLE:
      handle = PlatformHandle::ForHandle(platform_handle->value);
      break;
    case MOJO_PLATFORM_HANDLE_TYPE_FILE_DESCRIPTOR:
      handle = PlatformHandle::ForFd(platform_handle->value);
      break;

#elif defined(OS_POSIX)
    case MOJO_PLATFORM_HANDLE_TYPE_FILE_DESCRIPTOR:
      handle.handle = static_cast<int>(platform_handle->value);
      break;
#endif

#if defined(OS_MACOSX) && !defined(OS_IOS)
    case MOJO_PLATFORM_HANDLE_TYPE_MACH_PORT:
      handle.type = PlatformHandle::Type::MACH;
      handle.port = static_cast<mach_port_t>(platform_handle->value);
      break;
#endif

#if defined(OS_WIN)
    case MOJO_PLATFORM_HANDLE_TYPE_WINDOWS_HANDLE:
      handle.handle = reinterpret_cast<HANDLE>(platform_handle->value);
      break;
#endif

    default:
      return MOJO_RESULT_INVALID_ARGUMENT;
  }

  out_handle->reset(handle);
  return MOJO_RESULT_OK;
}
