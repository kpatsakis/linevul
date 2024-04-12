void AppendFormattedComponent(const std::string& spec,
                              const url_parse::Component& original_component,
                              const std::vector<size_t>& original_offsets,
                              const AppendComponentTransform& transform,
                              string16* output,
                              url_parse::Component* output_component,
                              std::vector<size_t>* offsets_for_adjustment) {
  DCHECK(output);
  if (original_component.is_nonempty()) {
    size_t original_component_begin =
        static_cast<size_t>(original_component.begin);
    size_t output_component_begin = output->length();
    if (output_component)
      output_component->begin = static_cast<int>(output_component_begin);

    std::vector<size_t> offsets_into_component =
        OffsetsIntoComponent(original_offsets, original_component_begin);
    output->append(transform.Execute(std::string(spec, original_component_begin,
        static_cast<size_t>(original_component.len)), &offsets_into_component));

    if (output_component) {
      output_component->len =
          static_cast<int>(output->length() - output_component_begin);
    }
    AdjustForComponentTransform(original_offsets, original_component_begin,
                                static_cast<size_t>(original_component.end()),
                                offsets_into_component, output_component_begin,
                                offsets_for_adjustment);
  } else if (output_component) {
    output_component->reset();
  }
}
