bool IsInstantTetheringBackgroundAdvertisingSupported() {
  return base::FeatureList::IsEnabled(
      kInstantTetheringBackgroundAdvertisementSupport);
}
