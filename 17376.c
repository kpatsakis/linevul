void HTMLMediaElement::SourceWasRemoved(HTMLSourceElement* source) {
  BLINK_MEDIA_LOG << "sourceWasRemoved(" << (void*)this << ", " << source
                  << ")";

  KURL url = source->GetNonEmptyURLAttribute(kSrcAttr);
  BLINK_MEDIA_LOG << "sourceWasRemoved(" << (void*)this << ") - 'src' is "
                  << UrlForLoggingMedia(url);

  if (source != current_source_node_ && source != next_child_node_to_consider_)
    return;

  if (source == next_child_node_to_consider_) {
    if (current_source_node_)
      next_child_node_to_consider_ = current_source_node_->nextSibling();
    BLINK_MEDIA_LOG << "sourceWasRemoved(" << (void*)this
                    << ") - next_child_node_to_consider_ set to "
                    << next_child_node_to_consider_.Get();
  } else if (source == current_source_node_) {
    current_source_node_ = nullptr;
    BLINK_MEDIA_LOG << "SourceWasRemoved(" << (void*)this
                    << ") - current_source_node_ set to 0";
  }
}
