int32_t PPB_URLLoader_Impl::Open(PP_Resource request_id,
                                 scoped_refptr<TrackedCallback> callback) {
  if (main_document_loader_)
    return PP_ERROR_INPROGRESS;

  EnterResourceNoLock<PPB_URLRequestInfo_API> enter_request(request_id, true);
  if (enter_request.failed()) {
    Log(PP_LOGLEVEL_ERROR,
        "PPB_URLLoader.Open: invalid request resource ID. (Hint to C++ wrapper"
        " users: use the ResourceRequest constructor that takes an instance or"
        " else the request will be null.)");
    return PP_ERROR_BADARGUMENT;
  }
  PPB_URLRequestInfo_Impl* request = static_cast<PPB_URLRequestInfo_Impl*>(
      enter_request.object());

  int32_t rv = ValidateCallback(callback);
  if (rv != PP_OK)
    return rv;

  if (request->RequiresUniversalAccess() && !has_universal_access_) {
    Log(PP_LOGLEVEL_ERROR, "PPB_URLLoader.Open: The URL you're requesting is "
        " on a different security origin than your plugin. To request "
        " cross-origin resources, see "
        " PP_URLREQUESTPROPERTY_ALLOWCROSSORIGINREQUESTS.");
    return PP_ERROR_NOACCESS;
  }

  if (loader_.get())
    return PP_ERROR_INPROGRESS;

  WebFrame* frame = GetFrameForResource(this);
  if (!frame)
    return PP_ERROR_FAILED;
  WebURLRequest web_request;
  if (!request->ToWebURLRequest(frame, &web_request))
    return PP_ERROR_FAILED;

  request_data_ = request->GetData();

  WebURLLoaderOptions options;
  if (has_universal_access_) {
    options.allowCredentials = true;
    options.crossOriginRequestPolicy =
        WebURLLoaderOptions::CrossOriginRequestPolicyAllow;
  } else {
    options.untrustedHTTP = true;
    if (request_data_.allow_cross_origin_requests) {
      options.allowCredentials = request_data_.allow_credentials;
      options.crossOriginRequestPolicy =
          WebURLLoaderOptions::CrossOriginRequestPolicyUseAccessControl;
    } else {
      options.allowCredentials = true;
    }
  }

  is_asynchronous_load_suspended_ = false;
  loader_.reset(frame->createAssociatedURLLoader(options));
  if (!loader_.get())
    return PP_ERROR_FAILED;

  loader_->loadAsynchronously(web_request, this);

  RegisterCallback(callback);
  return PP_OK_COMPLETIONPENDING;
}
