ResourceMultiBuffer::ResourceMultiBuffer(UrlData* url_data, int block_shift)
    : MultiBuffer(block_shift, url_data->url_index_->lru_),
      url_data_(url_data) {}
