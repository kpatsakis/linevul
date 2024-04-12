bool IsUsingLoFi(LoFiState lofi_state,
                 ResourceDispatcherHostDelegate* delegate,
                 const net::URLRequest& request,
                 ResourceContext* resource_context,
                 bool is_main_frame) {
  if (lofi_state == LOFI_UNSPECIFIED && delegate && is_main_frame)
    return delegate->ShouldEnableLoFiMode(request, resource_context);
  return lofi_state == LOFI_ON;
}
