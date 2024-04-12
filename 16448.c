const TransformationMatrix& GeometryMapper::SourceToDestinationProjection(
    const TransformPaintPropertyNode* source,
    const TransformPaintPropertyNode* destination) {
  DCHECK(source && destination);
  bool success = false;
  const auto& result =
      SourceToDestinationProjectionInternal(source, destination, success);
  return result;
}
