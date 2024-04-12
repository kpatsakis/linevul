ContentSecurityPolicy::ContentSecurityPolicy()
    : execution_context_(nullptr),
      override_inline_style_allowed_(false),
      script_hash_algorithms_used_(kContentSecurityPolicyHashAlgorithmNone),
      style_hash_algorithms_used_(kContentSecurityPolicyHashAlgorithmNone),
      sandbox_mask_(0),
      treat_as_public_address_(false),
      require_safe_types_(false),
      insecure_request_policy_(kLeaveInsecureRequestsAlone) {}
