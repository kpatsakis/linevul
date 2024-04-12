FLACExtractor::FLACExtractor(
 const sp<DataSource> &dataSource)
 : mDataSource(dataSource),
      mInitCheck(false)
{
    ALOGV("FLACExtractor::FLACExtractor");
    mInitCheck = init();
}
