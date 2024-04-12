void SVGStyleElement::FinishParsingChildren() {
  StyleElement::ProcessingResult result =
      StyleElement::FinishParsingChildren(*this);
  SVGElement::FinishParsingChildren();
  if (result == StyleElement::kProcessingFatalError)
    NotifyLoadedSheetAndAllCriticalSubresources(
        kErrorOccurredLoadingSubresource);
}
