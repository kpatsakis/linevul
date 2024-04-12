BlobURLRequestJob::~BlobURLRequestJob() {
  STLDeleteValues(&index_to_reader_);
}
