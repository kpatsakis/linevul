void RecordVariationSeedEmptyHistogram(VariationSeedEmptyState state) {
  UMA_HISTOGRAM_ENUMERATION("Variations.SeedEmpty", state,
                            VARIATIONS_SEED_EMPTY_ENUM_SIZE);
}
