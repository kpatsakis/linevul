String AXNodeObject::nativeTextAlternative(
    AXObjectSet& visited,
    AXNameFrom& nameFrom,
    AXRelatedObjectVector* relatedObjects,
    NameSources* nameSources,
    bool* foundTextAlternative) const {
  if (!getNode())
    return String();

  if (nameSources)
    ASSERT(relatedObjects);

  String textAlternative;
  AXRelatedObjectVector localRelatedObjects;

  const HTMLInputElement* inputElement = nullptr;
  if (isHTMLInputElement(getNode()))
    inputElement = toHTMLInputElement(getNode());

  HTMLElement* htmlElement = nullptr;
  if (getNode()->isHTMLElement())
    htmlElement = toHTMLElement(getNode());

  if (htmlElement && htmlElement->isLabelable()) {
    nameFrom = AXNameFromRelatedElement;
    if (nameSources) {
      nameSources->push_back(NameSource(*foundTextAlternative));
      nameSources->back().type = nameFrom;
      nameSources->back().nativeSource = AXTextFromNativeHTMLLabel;
    }

    LabelsNodeList* labels = toLabelableElement(htmlElement)->labels();
    if (labels && labels->length() > 0) {
      HeapVector<Member<Element>> labelElements;
      for (unsigned labelIndex = 0; labelIndex < labels->length();
           ++labelIndex) {
        Element* label = labels->item(labelIndex);
        if (nameSources) {
          if (!label->getAttribute(forAttr).isEmpty() &&
              label->getAttribute(forAttr) == htmlElement->getIdAttribute()) {
            nameSources->back().nativeSource = AXTextFromNativeHTMLLabelFor;
          } else {
            nameSources->back().nativeSource = AXTextFromNativeHTMLLabelWrapped;
          }
        }
        labelElements.push_back(label);
      }

      textAlternative =
          textFromElements(false, visited, labelElements, relatedObjects);
      if (!textAlternative.isNull()) {
        *foundTextAlternative = true;
        if (nameSources) {
          NameSource& source = nameSources->back();
          source.relatedObjects = *relatedObjects;
          source.text = textAlternative;
        } else {
          return textAlternative;
        }
      } else if (nameSources) {
        nameSources->back().invalid = true;
      }
    }
  }

  if (inputElement && inputElement->isTextButton()) {
    nameFrom = AXNameFromValue;
    if (nameSources) {
      nameSources->push_back(NameSource(*foundTextAlternative, valueAttr));
      nameSources->back().type = nameFrom;
    }
    String value = inputElement->value();
    if (!value.isNull()) {
      textAlternative = value;
      if (nameSources) {
        NameSource& source = nameSources->back();
        source.text = textAlternative;
        *foundTextAlternative = true;
      } else {
        return textAlternative;
      }
    }

    if (!getLayoutObject()) {
      String defaultLabel = inputElement->valueOrDefaultLabel();
      if (value.isNull() && !defaultLabel.isNull()) {
        nameFrom = AXNameFromContents;
        if (nameSources) {
          nameSources->push_back(NameSource(*foundTextAlternative));
          nameSources->back().type = nameFrom;
        }
        textAlternative = defaultLabel;
        if (nameSources) {
          NameSource& source = nameSources->back();
          source.text = textAlternative;
          *foundTextAlternative = true;
        } else {
          return textAlternative;
        }
      }
    }
    return textAlternative;
  }

  if (inputElement &&
      inputElement->getAttribute(typeAttr) == InputTypeNames::image) {
    nameFrom = AXNameFromAttribute;
    if (nameSources) {
      nameSources->push_back(NameSource(*foundTextAlternative, altAttr));
      nameSources->back().type = nameFrom;
    }
    const AtomicString& alt = inputElement->getAttribute(altAttr);
    if (!alt.isNull()) {
      textAlternative = alt;
      if (nameSources) {
        NameSource& source = nameSources->back();
        source.attributeValue = alt;
        source.text = textAlternative;
        *foundTextAlternative = true;
      } else {
        return textAlternative;
      }
    }

    if (nameSources) {
      nameSources->push_back(NameSource(*foundTextAlternative, valueAttr));
      nameSources->back().type = nameFrom;
    }
    nameFrom = AXNameFromAttribute;
    String value = inputElement->value();
    if (!value.isNull()) {
      textAlternative = value;
      if (nameSources) {
        NameSource& source = nameSources->back();
        source.text = textAlternative;
        *foundTextAlternative = true;
      } else {
        return textAlternative;
      }
    }

    nameFrom = AXNameFromValue;
    textAlternative = inputElement->locale().queryString(
        WebLocalizedString::SubmitButtonDefaultLabel);
    if (nameSources) {
      nameSources->push_back(NameSource(*foundTextAlternative, typeAttr));
      NameSource& source = nameSources->back();
      source.attributeValue = inputElement->getAttribute(typeAttr);
      source.type = nameFrom;
      source.text = textAlternative;
      *foundTextAlternative = true;
    } else {
      return textAlternative;
    }
    return textAlternative;
  }

  if (htmlElement && htmlElement->isTextControl()) {
    nameFrom = AXNameFromPlaceholder;
    if (nameSources) {
      nameSources->push_back(
          NameSource(*foundTextAlternative, placeholderAttr));
      NameSource& source = nameSources->back();
      source.type = nameFrom;
    }
    const String placeholder = placeholderFromNativeAttribute();
    if (!placeholder.isEmpty()) {
      textAlternative = placeholder;
      if (nameSources) {
        NameSource& source = nameSources->back();
        source.text = textAlternative;
        source.attributeValue = htmlElement->fastGetAttribute(placeholderAttr);
        *foundTextAlternative = true;
      } else {
        return textAlternative;
      }
    }

    nameFrom = AXNameFromPlaceholder;
    if (nameSources) {
      nameSources->push_back(
          NameSource(*foundTextAlternative, aria_placeholderAttr));
      NameSource& source = nameSources->back();
      source.type = nameFrom;
    }
    const AtomicString& ariaPlaceholder =
        getAOMPropertyOrARIAAttribute(AOMStringProperty::kPlaceholder);
    if (!ariaPlaceholder.isEmpty()) {
      textAlternative = ariaPlaceholder;
      if (nameSources) {
        NameSource& source = nameSources->back();
        source.text = textAlternative;
        source.attributeValue = ariaPlaceholder;
        *foundTextAlternative = true;
      } else {
        return textAlternative;
      }
    }

    return textAlternative;
  }

  if (getNode()->hasTagName(figureTag)) {
    nameFrom = AXNameFromRelatedElement;
    if (nameSources) {
      nameSources->push_back(NameSource(*foundTextAlternative));
      nameSources->back().type = nameFrom;
      nameSources->back().nativeSource = AXTextFromNativeHTMLFigcaption;
    }
    Element* figcaption = nullptr;
    for (Element& element : ElementTraversal::descendantsOf(*(getNode()))) {
      if (element.hasTagName(figcaptionTag)) {
        figcaption = &element;
        break;
      }
    }
    if (figcaption) {
      AXObject* figcaptionAXObject = axObjectCache().getOrCreate(figcaption);
      if (figcaptionAXObject) {
        textAlternative =
            recursiveTextAlternative(*figcaptionAXObject, false, visited);

        if (relatedObjects) {
          localRelatedObjects.push_back(
              new NameSourceRelatedObject(figcaptionAXObject, textAlternative));
          *relatedObjects = localRelatedObjects;
          localRelatedObjects.clear();
        }

        if (nameSources) {
          NameSource& source = nameSources->back();
          source.relatedObjects = *relatedObjects;
          source.text = textAlternative;
          *foundTextAlternative = true;
        } else {
          return textAlternative;
        }
      }
    }
    return textAlternative;
  }

  if (isHTMLImageElement(getNode()) || isHTMLAreaElement(getNode()) ||
      (getLayoutObject() && getLayoutObject()->isSVGImage())) {
    nameFrom = AXNameFromAttribute;
    if (nameSources) {
      nameSources->push_back(NameSource(*foundTextAlternative, altAttr));
      nameSources->back().type = nameFrom;
    }
    const AtomicString& alt = getAttribute(altAttr);
    if (!alt.isNull()) {
      textAlternative = alt;
      if (nameSources) {
        NameSource& source = nameSources->back();
        source.attributeValue = alt;
        source.text = textAlternative;
        *foundTextAlternative = true;
      } else {
        return textAlternative;
      }
    }
    return textAlternative;
  }

  if (isHTMLTableElement(getNode())) {
    HTMLTableElement* tableElement = toHTMLTableElement(getNode());

    nameFrom = AXNameFromCaption;
    if (nameSources) {
      nameSources->push_back(NameSource(*foundTextAlternative));
      nameSources->back().type = nameFrom;
      nameSources->back().nativeSource = AXTextFromNativeHTMLTableCaption;
    }
    HTMLTableCaptionElement* caption = tableElement->caption();
    if (caption) {
      AXObject* captionAXObject = axObjectCache().getOrCreate(caption);
      if (captionAXObject) {
        textAlternative =
            recursiveTextAlternative(*captionAXObject, false, visited);
        if (relatedObjects) {
          localRelatedObjects.push_back(
              new NameSourceRelatedObject(captionAXObject, textAlternative));
          *relatedObjects = localRelatedObjects;
          localRelatedObjects.clear();
        }

        if (nameSources) {
          NameSource& source = nameSources->back();
          source.relatedObjects = *relatedObjects;
          source.text = textAlternative;
          *foundTextAlternative = true;
        } else {
          return textAlternative;
        }
      }
    }

    nameFrom = AXNameFromAttribute;
    if (nameSources) {
      nameSources->push_back(NameSource(*foundTextAlternative, summaryAttr));
      nameSources->back().type = nameFrom;
    }
    const AtomicString& summary = getAttribute(summaryAttr);
    if (!summary.isNull()) {
      textAlternative = summary;
      if (nameSources) {
        NameSource& source = nameSources->back();
        source.attributeValue = summary;
        source.text = textAlternative;
        *foundTextAlternative = true;
      } else {
        return textAlternative;
      }
    }

    return textAlternative;
  }

  if (getNode()->isSVGElement()) {
    nameFrom = AXNameFromRelatedElement;
    if (nameSources) {
      nameSources->push_back(NameSource(*foundTextAlternative));
      nameSources->back().type = nameFrom;
      nameSources->back().nativeSource = AXTextFromNativeHTMLTitleElement;
    }
    ASSERT(getNode()->isContainerNode());
    Element* title = ElementTraversal::firstChild(
        toContainerNode(*(getNode())), HasTagName(SVGNames::titleTag));

    if (title) {
      AXObject* titleAXObject = axObjectCache().getOrCreate(title);
      if (titleAXObject && !visited.contains(titleAXObject)) {
        textAlternative =
            recursiveTextAlternative(*titleAXObject, false, visited);
        if (relatedObjects) {
          localRelatedObjects.push_back(
              new NameSourceRelatedObject(titleAXObject, textAlternative));
          *relatedObjects = localRelatedObjects;
          localRelatedObjects.clear();
        }
      }
      if (nameSources) {
        NameSource& source = nameSources->back();
        source.text = textAlternative;
        source.relatedObjects = *relatedObjects;
        *foundTextAlternative = true;
      } else {
        return textAlternative;
      }
    }
  }

  if (isHTMLFieldSetElement(getNode())) {
    nameFrom = AXNameFromRelatedElement;
    if (nameSources) {
      nameSources->push_back(NameSource(*foundTextAlternative));
      nameSources->back().type = nameFrom;
      nameSources->back().nativeSource = AXTextFromNativeHTMLLegend;
    }
    HTMLElement* legend = toHTMLFieldSetElement(getNode())->legend();
    if (legend) {
      AXObject* legendAXObject = axObjectCache().getOrCreate(legend);
      if (legendAXObject && !visited.contains(legendAXObject)) {
        textAlternative =
            recursiveTextAlternative(*legendAXObject, false, visited);

        if (relatedObjects) {
          localRelatedObjects.push_back(
              new NameSourceRelatedObject(legendAXObject, textAlternative));
          *relatedObjects = localRelatedObjects;
          localRelatedObjects.clear();
        }

        if (nameSources) {
          NameSource& source = nameSources->back();
          source.relatedObjects = *relatedObjects;
          source.text = textAlternative;
          *foundTextAlternative = true;
        } else {
          return textAlternative;
        }
      }
    }
  }

  if (isWebArea()) {
    Document* document = this->getDocument();
    if (document) {
      nameFrom = AXNameFromAttribute;
      if (nameSources) {
        nameSources->push_back(
            NameSource(foundTextAlternative, aria_labelAttr));
        nameSources->back().type = nameFrom;
      }
      if (Element* documentElement = document->documentElement()) {
        const AtomicString& ariaLabel = AccessibleNode::getProperty(
            documentElement, AOMStringProperty::kLabel);
        if (!ariaLabel.isEmpty()) {
          textAlternative = ariaLabel;

          if (nameSources) {
            NameSource& source = nameSources->back();
            source.text = textAlternative;
            source.attributeValue = ariaLabel;
            *foundTextAlternative = true;
          } else {
            return textAlternative;
          }
        }
      }

      nameFrom = AXNameFromRelatedElement;
      if (nameSources) {
        nameSources->push_back(NameSource(*foundTextAlternative));
        nameSources->back().type = nameFrom;
        nameSources->back().nativeSource = AXTextFromNativeHTMLTitleElement;
      }

      textAlternative = document->title();

      Element* titleElement = document->titleElement();
      AXObject* titleAXObject = axObjectCache().getOrCreate(titleElement);
      if (titleAXObject) {
        if (relatedObjects) {
          localRelatedObjects.push_back(
              new NameSourceRelatedObject(titleAXObject, textAlternative));
          *relatedObjects = localRelatedObjects;
          localRelatedObjects.clear();
        }

        if (nameSources) {
          NameSource& source = nameSources->back();
          source.relatedObjects = *relatedObjects;
          source.text = textAlternative;
          *foundTextAlternative = true;
        } else {
          return textAlternative;
        }
      }
    }
  }

  return textAlternative;
}
