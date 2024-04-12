void RTCPeerConnection::didGenerateIceCandidate(PassRefPtr<RTCIceCandidateDescriptor> iceCandidateDescriptor)
{
    ASSERT(scriptExecutionContext()->isContextThread());
    if (!iceCandidateDescriptor)
        dispatchEvent(RTCIceCandidateEvent::create(false, false, 0));
    else {
        RefPtr<RTCIceCandidate> iceCandidate = RTCIceCandidate::create(iceCandidateDescriptor);
        dispatchEvent(RTCIceCandidateEvent::create(false, false, iceCandidate.release()));
    }
}
