void FramerVisitorCapturingAcks::OnAckFrame(const QuicAckFrame& frame) {
   frame_ = frame;
 }
