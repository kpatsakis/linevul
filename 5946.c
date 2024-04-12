void ImageResource::Finish(double load_finish_time,
                           base::SingleThreadTaskRunner* task_runner) {
  if (multipart_parser_) {
    multipart_parser_->Finish();
    if (Data())
      UpdateImageAndClearBuffer();
  } else {
    UpdateImage(Data(), ImageResourceContent::kUpdateImage, true);
    ClearData();
  }
  Resource::Finish(load_finish_time, task_runner);
}
