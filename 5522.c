LocalFrame* WebLocalFrameImpl::CreateChildFrame(
    const AtomicString& name,
    HTMLFrameOwnerElement* owner_element) {
  DCHECK(client_);
  TRACE_EVENT0("blink", "WebLocalFrameImpl::createChildframe");
  WebTreeScopeType scope =
      GetFrame()->GetDocument() == owner_element->GetTreeScope()
          ? WebTreeScopeType::kDocument
          : WebTreeScopeType::kShadow;
  WebFrameOwnerProperties owner_properties(
      owner_element->BrowsingContextContainerName(),
      owner_element->ScrollingMode(), owner_element->MarginWidth(),
      owner_element->MarginHeight(), owner_element->AllowFullscreen(),
      owner_element->AllowPaymentRequest(), owner_element->IsDisplayNone(),
      owner_element->Csp(), owner_element->AllowedFeatures());
  WebLocalFrameImpl* webframe_child =
      ToWebLocalFrameImpl(client_->CreateChildFrame(
          this, scope, name,
          owner_element->getAttribute(
              owner_element->SubResourceAttributeName()),
          static_cast<WebSandboxFlags>(owner_element->GetSandboxFlags()),
          owner_element->ContainerPolicy(), owner_properties));
  if (!webframe_child)
    return nullptr;

  webframe_child->InitializeCoreFrame(*GetFrame()->GetPage(), owner_element,
                                      name);
  DCHECK(webframe_child->Parent());
  return webframe_child->GetFrame();
}
