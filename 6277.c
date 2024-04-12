std::string DownloadResourceHandler::DebugString() const {
  const ResourceRequestInfoImpl* info = GetRequestInfo();
  return base::StringPrintf("{"
                            " url_ = " "\"%s\""
                            " info = {"
                            " child_id = " "%d"
                            " request_id = " "%d"
                            " route_id = " "%d"
                            " }"
                            " }",
                            request() ?
                                request()->url().spec().c_str() :
                                "<NULL request>",
                            info->GetChildID(),
                            info->GetRequestID(),
                            info->GetRouteID());
}
