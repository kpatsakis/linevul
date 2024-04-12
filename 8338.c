  String DumpFragmentTree(Element* element) {
    auto fragment = RunBlockLayoutAlgorithm(element);
    return DumpFragmentTree(fragment.get());
  }
