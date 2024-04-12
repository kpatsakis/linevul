Node* Document::importNode(Node* importedNode, bool deep, ExceptionState& exceptionState)
{
    switch (importedNode->getNodeType()) {
    case TEXT_NODE:
        return createTextNode(importedNode->nodeValue());
    case CDATA_SECTION_NODE:
        return CDATASection::create(*this, importedNode->nodeValue());
    case PROCESSING_INSTRUCTION_NODE:
        return createProcessingInstruction(importedNode->nodeName(), importedNode->nodeValue(), exceptionState);
    case COMMENT_NODE:
        return createComment(importedNode->nodeValue());
    case DOCUMENT_TYPE_NODE: {
        DocumentType* doctype = toDocumentType(importedNode);
        return DocumentType::create(this, doctype->name(), doctype->publicId(), doctype->systemId());
    }
    case ELEMENT_NODE: {
        Element* oldElement = toElement(importedNode);
        if (!hasValidNamespaceForElements(oldElement->tagQName())) {
            exceptionState.throwDOMException(NamespaceError, "The imported node has an invalid namespace.");
            return nullptr;
        }
        Element* newElement = createElement(oldElement->tagQName(), CreatedByImportNode);

        newElement->cloneDataFromElement(*oldElement);

        if (deep) {
            if (!importContainerNodeChildren(oldElement, newElement, exceptionState))
                return nullptr;
            if (isHTMLTemplateElement(*oldElement)
                && !ensureTemplateDocument().importContainerNodeChildren(
                    toHTMLTemplateElement(oldElement)->content(),
                    toHTMLTemplateElement(newElement)->content(), exceptionState))
                return nullptr;
        }

        return newElement;
    }
    case ATTRIBUTE_NODE:
        return Attr::create(*this, QualifiedName(nullAtom, AtomicString(toAttr(importedNode)->name()), nullAtom), toAttr(importedNode)->value());
    case DOCUMENT_FRAGMENT_NODE: {
        if (importedNode->isShadowRoot()) {
            exceptionState.throwDOMException(NotSupportedError, "The node provided is a shadow root, which may not be imported.");
            return nullptr;
        }
        DocumentFragment* oldFragment = toDocumentFragment(importedNode);
        DocumentFragment* newFragment = createDocumentFragment();
        if (deep && !importContainerNodeChildren(oldFragment, newFragment, exceptionState))
            return nullptr;

        return newFragment;
    }
    case DOCUMENT_NODE:
        exceptionState.throwDOMException(NotSupportedError, "The node provided is a document, which may not be imported.");
        return nullptr;
    }

    ASSERT_NOT_REACHED();
    return nullptr;
}
