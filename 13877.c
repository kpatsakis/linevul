  TestDeferringNavigationThrottleInstaller(
      WebContents* web_contents,
      NavigationThrottle::ThrottleCheckResult will_start_result,
      NavigationThrottle::ThrottleCheckResult will_redirect_result,
      NavigationThrottle::ThrottleCheckResult will_fail_result,
      NavigationThrottle::ThrottleCheckResult will_process_result,
      GURL expected_start_url = GURL())
      : TestNavigationThrottleInstaller(web_contents,
                                        NavigationThrottle::DEFER,
                                        NavigationThrottle::DEFER,
                                        NavigationThrottle::DEFER,
                                        NavigationThrottle::DEFER,
                                        expected_start_url),
        will_start_deferred_result_(will_start_result),
        will_redirect_deferred_result_(will_redirect_result),
        will_fail_deferred_result_(will_fail_result),
        will_process_deferred_result_(will_process_result) {}
