bool CanonicalizeScheme(const base::char16* spec,
                        const Component& scheme,
                        CanonOutput* output,
                        Component* out_scheme) {
  return DoScheme<base::char16, base::char16>(spec, scheme, output, out_scheme);
}
