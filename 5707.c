void ATSParser::PSISection::clear() {
 if (mBuffer != NULL) {
        mBuffer->setRange(0, 0);
 }
    mSkipBytes = 0;
}
