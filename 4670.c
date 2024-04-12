void DataPipeProducerDispatcher::NotifyWrite(uint32_t num_bytes) {
  DVLOG(1) << "Data pipe producer " << pipe_id_
           << " notifying peer: " << num_bytes
           << " bytes written. [control_port=" << control_port_.name() << "]";

  SendDataPipeControlMessage(node_controller_, control_port_,
                             DataPipeCommand::DATA_WAS_WRITTEN, num_bytes);
}
