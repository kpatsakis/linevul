static HistoryCommitType LoadTypeToCommitType(FrameLoadType type) {
  switch (type) {
    case kFrameLoadTypeStandard:
      return kStandardCommit;
    case kFrameLoadTypeInitialInChildFrame:
    case kFrameLoadTypeInitialHistoryLoad:
      return kInitialCommitInChildFrame;
    case kFrameLoadTypeBackForward:
      return kBackForwardCommit;
    default:
      break;
  }
  return kHistoryInertCommit;
}
