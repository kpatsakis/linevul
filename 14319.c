MojoResult ScopedPlatformHandleToMojoPlatformHandle(
    ScopedPlatformHandle handle,
    MojoPlatformHandle* platform_handle) {
  if (platform_handle->struct_size != sizeof(MojoPlatformHandle))
    return MOJO_RESULT_INVALID_ARGUMENT;

  if (!handle.is_valid()) {
    platform_handle->type = MOJO_PLATFORM_HANDLE_TYPE_INVALID;
    return MOJO_RESULT_OK;
  }

#if defined(OS_FUCHSIA)
  if (handle.get().is_valid_fd()) {
    platform_handle->type = MOJO_PLATFORM_HANDLE_TYPE_FILE_DESCRIPTOR;
    platform_handle->value = handle.release().as_fd();
  } else {
    platform_handle->type = MOJO_PLATFORM_HANDLE_TYPE_FUCHSIA_HANDLE;
    platform_handle->value = handle.release().as_handle();
  }
#elif defined(OS_POSIX)
  switch (handle.get().type) {
    case PlatformHandle::Type::POSIX:
      platform_handle->type = MOJO_PLATFORM_HANDLE_TYPE_FILE_DESCRIPTOR;
      platform_handle->value = static_cast<uint64_t>(handle.release().handle);
      break;

#if defined(OS_MACOSX) && !defined(OS_IOS)
    case PlatformHandle::Type::MACH:
      platform_handle->type = MOJO_PLATFORM_HANDLE_TYPE_MACH_PORT;
      platform_handle->value = static_cast<uint64_t>(handle.release().port);
      break;
#endif  // defined(OS_MACOSX) && !defined(OS_IOS)

    default:
      return MOJO_RESULT_INVALID_ARGUMENT;
  }
#elif defined(OS_WIN)
  platform_handle->type = MOJO_PLATFORM_HANDLE_TYPE_WINDOWS_HANDLE;
  platform_handle->value = reinterpret_cast<uint64_t>(handle.release().handle);
#endif  // defined(OS_WIN)

  return MOJO_RESULT_OK;
}
