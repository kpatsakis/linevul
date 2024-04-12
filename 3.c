HTMLTreeBuilderSimulator::State HTMLTreeBuilderSimulator::StateFor(
    HTMLTreeBuilder* tree_builder) {
  DCHECK(IsMainThread());
  State namespace_stack;
  for (HTMLElementStack::ElementRecord* record =
           tree_builder->OpenElements()->TopRecord();
       record; record = record->Next()) {
    Namespace current_namespace = HTML;
    if (record->NamespaceURI() == SVGNames::svgNamespaceURI)
      current_namespace = SVG;
    else if (record->NamespaceURI() == MathMLNames::mathmlNamespaceURI)
      current_namespace = kMathML;

    if (namespace_stack.IsEmpty() ||
        namespace_stack.back() != current_namespace)
      namespace_stack.push_back(current_namespace);
  }
  namespace_stack.Reverse();
  return namespace_stack;
}
