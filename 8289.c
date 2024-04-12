  void UninitializeStatisticsRecorder() {
    statistics_recorder_.reset();
    delete StatisticsRecorder::top_;
    DCHECK(!StatisticsRecorder::top_);
  }
