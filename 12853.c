CSSPropertyID SVGElement::CssPropertyIdForSVGAttributeName(
    const QualifiedName& attr_name) {
  if (!attr_name.NamespaceURI().IsNull())
    return CSSPropertyInvalid;

  static HashMap<StringImpl*, CSSPropertyID>* property_name_to_id_map = nullptr;
  if (!property_name_to_id_map) {
    property_name_to_id_map = new HashMap<StringImpl*, CSSPropertyID>;
    const QualifiedName* const attr_names[] = {
        &kAlignmentBaselineAttr,
        &kBaselineShiftAttr,
        &kBufferedRenderingAttr,
        &kClipAttr,
        &kClipPathAttr,
        &kClipRuleAttr,
        &svg_names::kColorAttr,
        &kColorInterpolationAttr,
        &kColorInterpolationFiltersAttr,
        &kColorRenderingAttr,
        &kCursorAttr,
        &svg_names::kDirectionAttr,
        &kDisplayAttr,
        &kDominantBaselineAttr,
        &kFillAttr,
        &kFillOpacityAttr,
        &kFillRuleAttr,
        &kFilterAttr,
        &kFloodColorAttr,
        &kFloodOpacityAttr,
        &kFontFamilyAttr,
        &kFontSizeAttr,
        &kFontStretchAttr,
        &kFontStyleAttr,
        &kFontVariantAttr,
        &kFontWeightAttr,
        &kImageRenderingAttr,
        &kLetterSpacingAttr,
        &kLightingColorAttr,
        &kMarkerEndAttr,
        &kMarkerMidAttr,
        &kMarkerStartAttr,
        &kMaskAttr,
        &kMaskTypeAttr,
        &kOpacityAttr,
        &kOverflowAttr,
        &kPaintOrderAttr,
        &kPointerEventsAttr,
        &kShapeRenderingAttr,
        &kStopColorAttr,
        &kStopOpacityAttr,
        &kStrokeAttr,
        &kStrokeDasharrayAttr,
        &kStrokeDashoffsetAttr,
        &kStrokeLinecapAttr,
        &kStrokeLinejoinAttr,
        &kStrokeMiterlimitAttr,
        &kStrokeOpacityAttr,
        &kStrokeWidthAttr,
        &kTextAnchorAttr,
        &kTextDecorationAttr,
        &kTextRenderingAttr,
        &kTransformOriginAttr,
        &kUnicodeBidiAttr,
        &kVectorEffectAttr,
        &kVisibilityAttr,
        &kWordSpacingAttr,
        &kWritingModeAttr,
    };
    for (size_t i = 0; i < arraysize(attr_names); i++) {
      CSSPropertyID property_id = cssPropertyID(attr_names[i]->LocalName());
      DCHECK_GT(property_id, 0);
      property_name_to_id_map->Set(attr_names[i]->LocalName().Impl(),
                                   property_id);
    }
  }

  return property_name_to_id_map->at(attr_name.LocalName().Impl());
}
