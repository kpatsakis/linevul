FLACSource::~FLACSource()
{
    ALOGV("~FLACSource::FLACSource");
 if (mStarted) {
        stop();
 }
}
