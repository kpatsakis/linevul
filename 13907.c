void H264DPB::GetShortTermRefPicsAppending(H264Picture::PtrVector& out) {
  for (size_t i = 0; i < pics_.size(); ++i) {
    H264Picture* pic = pics_[i];
    if (pic->ref && !pic->long_term)
      out.push_back(pic);
  }
}
