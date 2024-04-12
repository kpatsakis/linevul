void ATSParser::Program::signalDiscontinuity(
 DiscontinuityType type, const sp<AMessage> &extra) {
 int64_t mediaTimeUs;
 if ((type & DISCONTINUITY_TIME)
 && extra != NULL
 && extra->findInt64(
 IStreamListener::kKeyMediaTimeUs, &mediaTimeUs)) {
        mFirstPTSValid = false;
 }

 for (size_t i = 0; i < mStreams.size(); ++i) {
        mStreams.editValueAt(i)->signalDiscontinuity(type, extra);
 }
}
