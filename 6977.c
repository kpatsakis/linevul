std::unique_ptr<base::Value> StringVectorToValue(
    const std::vector<std::string>& strings) {
  ListBuilder builder;
  for (const auto& str : strings)
    builder.Append(str);
  return builder.Build();
}
