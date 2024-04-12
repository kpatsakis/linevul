scoped_refptr<UploadData> CreateSimpleUploadData(const char* data) {
  scoped_refptr<UploadData> upload(new UploadData);
  upload->AppendBytes(data, strlen(data));
  return upload;
}
