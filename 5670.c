void ReportUserActionHistogram(enum UserActionBuckets event) {
  UMA_HISTOGRAM_ENUMERATION("PrintPreview.UserAction", event,
                            USERACTION_BUCKET_BOUNDARY);
}
