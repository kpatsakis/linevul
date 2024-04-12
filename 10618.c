void GranularityStrategyTest::ParseText(Text* text) {
  TextNodeVector text_nodes;
  text_nodes.push_back(text);
  ParseText(text_nodes);
}
