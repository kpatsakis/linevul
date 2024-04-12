void SampleIterator::reset() {
    mSampleToChunkIndex = 0;
    mFirstChunk = 0;
    mFirstChunkSampleIndex = 0;
    mStopChunk = 0;
    mStopChunkSampleIndex = 0;
    mSamplesPerChunk = 0;
    mChunkDesc = 0;
}
