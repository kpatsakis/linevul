void ID3::Iterator::findFrame() {
 for (;;) {
        mFrameData = NULL;
        mFrameSize = 0;

 if (mParent.mVersion == ID3_V2_2) {
 if (mOffset + 6 > mParent.mSize) {
 return;
 }

 if (!memcmp(&mParent.mData[mOffset], "\0\0\0", 3)) {
 return;
 }

            mFrameSize =
 (mParent.mData[mOffset + 3] << 16)
 | (mParent.mData[mOffset + 4] << 8)
 | mParent.mData[mOffset + 5];

 if (mFrameSize == 0) {
 return;
 }
            mFrameSize += 6; // add tag id and size field

 if (SIZE_MAX - mOffset <= mFrameSize) {
 return;
 }

 if (mOffset + mFrameSize > mParent.mSize) {
                ALOGV("partial frame at offset %zu (size = %zu, bytes-remaining = %zu)",
                    mOffset, mFrameSize, mParent.mSize - mOffset - (size_t)6);
 return;
 }

            mFrameData = &mParent.mData[mOffset + 6];

 if (!mID) {
 break;
 }

 char id[4];
            memcpy(id, &mParent.mData[mOffset], 3);
            id[3] = '\0';

 if (!strcmp(id, mID)) {
 break;
 }
 } else if (mParent.mVersion == ID3_V2_3
 || mParent.mVersion == ID3_V2_4) {
 if (mOffset + 10 > mParent.mSize) {
 return;
 }

 if (!memcmp(&mParent.mData[mOffset], "\0\0\0\0", 4)) {
 return;
 }

 size_t baseSize = 0;
 if (mParent.mVersion == ID3_V2_4) {
 if (!ParseSyncsafeInteger(
 &mParent.mData[mOffset + 4], &baseSize)) {
 return;
 }
 } else {
                baseSize = U32_AT(&mParent.mData[mOffset + 4]);
 }

 if (baseSize == 0) {
 return;
 }

 if (SIZE_MAX - 10 <= baseSize) {
 return;
 }

            mFrameSize = 10 + baseSize; // add tag id, size field and flags

 if (SIZE_MAX - mOffset <= mFrameSize) {
 return;
 }

 if (mOffset + mFrameSize > mParent.mSize) {
                ALOGV("partial frame at offset %zu (size = %zu, bytes-remaining = %zu)",
                    mOffset, mFrameSize, mParent.mSize - mOffset - (size_t)10);
 return;
 }

 uint16_t flags = U16_AT(&mParent.mData[mOffset + 8]);

 if ((mParent.mVersion == ID3_V2_4 && (flags & 0x000c))
 || (mParent.mVersion == ID3_V2_3 && (flags & 0x00c0))) {

                ALOGV("Skipping unsupported frame (compression, encryption "
 "or per-frame unsynchronization flagged");

                mOffset += mFrameSize;
 continue;
 }

            mFrameData = &mParent.mData[mOffset + 10];

 if (!mID) {
 break;
 }

 char id[5];
            memcpy(id, &mParent.mData[mOffset], 4);
            id[4] = '\0';

 if (!strcmp(id, mID)) {
 break;
 }
 } else {
            CHECK(mParent.mVersion == ID3_V1 || mParent.mVersion == ID3_V1_1);

 if (mOffset >= mParent.mSize) {
 return;
 }

            mFrameData = &mParent.mData[mOffset];

 switch (mOffset) {
 case 3:
 case 33:
 case 63:
                    mFrameSize = 30;
 break;
 case 93:
                    mFrameSize = 4;
 break;
 case 97:
 if (mParent.mVersion == ID3_V1) {
                        mFrameSize = 30;
 } else {
                        mFrameSize = 29;
 }
 break;
 case 126:
                    mFrameSize = 1;
 break;
 case 127:
                    mFrameSize = 1;
 break;
 default:
                    CHECK(!"Should not be here, invalid offset.");
 break;
 }

 if (!mID) {
 break;
 }

 String8 id;
            getID(&id);

 if (id == mID) {
 break;
 }
 }

        mOffset += mFrameSize;

     }
 }
