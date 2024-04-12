void GLES2DecoderPassthroughImpl::SetQueryCallback(unsigned int query_client_id,
                                                   base::OnceClosure callback) {
  GLuint service_id = query_id_map_.GetServiceIDOrInvalid(query_client_id);
  for (auto& pending_query : pending_queries_) {
    if (pending_query.service_id == service_id) {
      pending_query.callbacks.push_back(std::move(callback));
      return;
    }
  }

  VLOG(1) << "GLES2DecoderPassthroughImpl::SetQueryCallback: No pending query "
             "with ID "
          << query_client_id << ". Running the callback immediately.";
  std::move(callback).Run();
}
