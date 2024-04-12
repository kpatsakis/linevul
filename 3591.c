void SVGElement::ReportAttributeParsingError(SVGParsingError error,
                                             const QualifiedName& name,
                                             const AtomicString& value) {
  if (error == SVGParseStatus::kNoError)
    return;
  if (value.IsNull())
    return;
  GetDocument().AddConsoleMessage(
      ConsoleMessage::Create(kRenderingMessageSource, kErrorMessageLevel,
                             "Error: " + error.Format(tagName(), name, value)));
}
