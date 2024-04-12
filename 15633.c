void HTMLMediaElement::setSrcObject(MediaStreamDescriptor* srcObject) {
  BLINK_MEDIA_LOG << "setSrcObject(" << (void*)this << ")";
  m_srcObject = srcObject;
  invokeLoadAlgorithm();
}
