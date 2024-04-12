void PaintController::AddToIndicesByClientMap(const DisplayItemClient& client,
                                              size_t index,
                                              IndicesByClientMap& map) {
  auto it = map.find(&client);
  auto& indices =
      it == map.end()
          ? map.insert(&client, Vector<size_t>()).stored_value->value
          : it->value;
  indices.push_back(index);
}
