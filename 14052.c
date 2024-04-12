bool InspectorPageAgent::SharedBufferContent(RefPtr<const SharedBuffer> buffer,
                                             const String& mime_type,
                                             const String& text_encoding_name,
                                             String* result,
                                             bool* base64_encoded) {
  if (!buffer)
    return false;

  String text_content;
  std::unique_ptr<TextResourceDecoder> decoder =
      CreateResourceTextDecoder(mime_type, text_encoding_name);
  WTF::TextEncoding encoding(text_encoding_name);

  const SharedBuffer::DeprecatedFlatData flat_buffer(std::move(buffer));
  if (decoder) {
    text_content = decoder->Decode(flat_buffer.Data(), flat_buffer.size());
    text_content = text_content + decoder->Flush();
  } else if (encoding.IsValid()) {
    text_content = encoding.Decode(flat_buffer.Data(), flat_buffer.size());
  }

  MaybeEncodeTextContent(text_content, flat_buffer.Data(), flat_buffer.size(),
                         result, base64_encoded);
  return true;
}
