bool Document::HasValidNamespaceForElements(const QualifiedName& q_name) {
  if (!q_name.Prefix().IsEmpty() && q_name.NamespaceURI().IsNull())
    return false;
  if (q_name.Prefix() == g_xml_atom &&
      q_name.NamespaceURI() != xml_names::kNamespaceURI)
    return false;

  if (q_name.Prefix() == g_xmlns_atom ||
      (q_name.Prefix().IsEmpty() && q_name.LocalName() == g_xmlns_atom))
    return q_name.NamespaceURI() == xmlns_names::kNamespaceURI;
  return q_name.NamespaceURI() != xmlns_names::kNamespaceURI;
}
