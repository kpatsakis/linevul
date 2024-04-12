bool ATSParser::PSISection::isComplete() const {
 if (mBuffer == NULL || mBuffer->size() < 3) {
 return false;
 }

 unsigned sectionLength = U16_AT(mBuffer->data() + 1) & 0xfff;
 return mBuffer->size() >= sectionLength + 3;
}
