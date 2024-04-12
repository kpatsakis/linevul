  MockMultibufferDataSource(
      const scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
      scoped_refptr<UrlData> url_data,
      BufferedDataSourceHost* host)
      : MultibufferDataSource(
            task_runner,
            std::move(url_data),
            &media_log_,
            host,
            base::Bind(&MockMultibufferDataSource::set_downloading,
                       base::Unretained(this))),
        downloading_(false) {}
