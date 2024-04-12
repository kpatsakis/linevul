static int CompareSoftwareCodecsFirst(
 const OMXCodec::CodecNameAndQuirks *elem1,
 const OMXCodec::CodecNameAndQuirks *elem2) {
 bool isOMX1 = !strncmp(elem1->mName.string(), "OMX.", 4);
 bool isOMX2 = !strncmp(elem2->mName.string(), "OMX.", 4);

 bool isSoftwareCodec1 = IsSoftwareCodec(elem1->mName.string());
 bool isSoftwareCodec2 = IsSoftwareCodec(elem2->mName.string());

 if (isSoftwareCodec1) {
 if (!isSoftwareCodec2) { return -1; }

 if (isOMX1) {
 if (isOMX2) { return 0; }

 return -1;
 } else {
 if (isOMX2) { return 0; }

 return 1;
 }

 return -1;
 }

 if (isSoftwareCodec2) {
 return 1;
 }

 return 0;
}
