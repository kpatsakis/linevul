void MidiManagerUsb::ReceiveUsbMidiData(UsbMidiDevice* device,
                                        int endpoint_number,
                                        const uint8* data,
                                        size_t size,
                                        base::TimeTicks time) {
  if (!input_stream_)
    return;
  input_stream_->OnReceivedData(device,
                                endpoint_number,
                                data,
                                size,
                                time);
}
