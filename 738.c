static bool IsUnicodeBidiNestedOrMultipleEmbeddings(CSSValueID value_id) {
  return value_id == CSSValueEmbed || value_id == CSSValueBidiOverride ||
         value_id == CSSValueWebkitIsolate ||
         value_id == CSSValueWebkitIsolateOverride ||
         value_id == CSSValueWebkitPlaintext || value_id == CSSValueIsolate ||
         value_id == CSSValueIsolateOverride || value_id == CSSValuePlaintext;
}
