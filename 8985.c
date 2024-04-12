void ChildThread::OnGetChildProfilerData(int sequence_number) {
  tracked_objects::ProcessDataSnapshot process_data;
  ThreadData::Snapshot(false, &process_data);

  Send(new ChildProcessHostMsg_ChildProfilerData(sequence_number,
                                                 process_data));
}
