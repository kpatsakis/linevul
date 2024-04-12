 static PropertyDetails GetDetailsImpl(JSObject* holder, uint32_t entry) {
 FixedArray* parameter_map = FixedArray::cast(holder->elements());
 uint32_t length = parameter_map->length() - 2;
 if (entry < length) {
 return PropertyDetails(kData, NONE, 0, PropertyCellType::kNoCell);
 }
 FixedArray* arguments = FixedArray::cast(parameter_map->get(1));
 return ArgumentsAccessor::GetDetailsImpl(arguments, entry - length);
 }
