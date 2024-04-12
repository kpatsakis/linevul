void PrintWebViewHelper::PrintNode(WebNode* node,
                                   bool script_initiated,
                                   bool is_preview) {
  Print(node->document().frame(), node, script_initiated, is_preview);
}
