blink::ParsedFeaturePolicy CreateFPHeaderMatchesAll(
    blink::mojom::FeaturePolicyFeature feature) {
  blink::ParsedFeaturePolicy result(1);
  result[0].feature = feature;
  result[0].matches_all_origins = true;
  return result;
}
