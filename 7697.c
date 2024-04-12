void RenderFrameImpl::OnGetSerializedHtmlWithLocalLinks(
    const std::map<GURL, base::FilePath>& url_to_local_path,
    const std::map<int, base::FilePath>& frame_routing_id_to_local_path) {
  LinkRewritingDelegate delegate(url_to_local_path,
                                 frame_routing_id_to_local_path);

  WebFrameSerializer::Serialize(GetWebFrame(),
                                this,  // WebFrameSerializerClient.
                                &delegate);
}
