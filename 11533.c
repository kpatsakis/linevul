  void InitializeWithCORS(const char* url,
                          bool expected,
                          UrlData::CORSMode cors_mode,
                          size_t file_size = kFileSize) {
    GURL gurl(url);
    data_source_.reset(new MockMultibufferDataSource(
        base::ThreadTaskRunnerHandle::Get(),
        url_index_->GetByUrl(gurl, cors_mode), &host_));
    data_source_->SetPreload(preload_);

    response_generator_.reset(new TestResponseGenerator(gurl, file_size));
    EXPECT_CALL(*this, OnInitialize(expected));
    data_source_->Initialize(base::Bind(
        &MultibufferDataSourceTest::OnInitialize, base::Unretained(this)));
    base::RunLoop().RunUntilIdle();

    EXPECT_EQ(data_source_->downloading(), false);
  }
