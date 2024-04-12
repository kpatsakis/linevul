  TestNavigationManagerThrottle(NavigationHandle* handle,
                                base::Closure on_will_start_request_closure,
                                base::Closure on_will_process_response_closure)
      : NavigationThrottle(handle),
        on_will_start_request_closure_(on_will_start_request_closure),
        on_will_process_response_closure_(on_will_process_response_closure) {}
