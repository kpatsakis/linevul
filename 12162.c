void fillWidgetProperties(AXObject& axObject,
                          protocol::Array<AXProperty>& properties) {
  AccessibilityRole role = axObject.roleValue();
  String autocomplete = axObject.ariaAutoComplete();
  if (!autocomplete.isEmpty())
    properties.addItem(
        createProperty(AXWidgetAttributesEnum::Autocomplete,
                       createValue(autocomplete, AXValueTypeEnum::Token)));

  if (axObject.hasAttribute(HTMLNames::aria_haspopupAttr)) {
    bool hasPopup = axObject.ariaHasPopup();
    properties.addItem(createProperty(AXWidgetAttributesEnum::Haspopup,
                                      createBooleanValue(hasPopup)));
  }

  int headingLevel = axObject.headingLevel();
  if (headingLevel > 0) {
    properties.addItem(createProperty(AXWidgetAttributesEnum::Level,
                                      createValue(headingLevel)));
  }
  int hierarchicalLevel = axObject.hierarchicalLevel();
  if (hierarchicalLevel > 0 ||
      axObject.hasAttribute(HTMLNames::aria_levelAttr)) {
    properties.addItem(createProperty(AXWidgetAttributesEnum::Level,
                                      createValue(hierarchicalLevel)));
  }

  if (roleAllowsMultiselectable(role)) {
    bool multiselectable = axObject.isMultiSelectable();
    properties.addItem(createProperty(AXWidgetAttributesEnum::Multiselectable,
                                      createBooleanValue(multiselectable)));
  }

  if (roleAllowsOrientation(role)) {
    AccessibilityOrientation orientation = axObject.orientation();
    switch (orientation) {
      case AccessibilityOrientationVertical:
        properties.addItem(
            createProperty(AXWidgetAttributesEnum::Orientation,
                           createValue("vertical", AXValueTypeEnum::Token)));
        break;
      case AccessibilityOrientationHorizontal:
        properties.addItem(
            createProperty(AXWidgetAttributesEnum::Orientation,
                           createValue("horizontal", AXValueTypeEnum::Token)));
        break;
      case AccessibilityOrientationUndefined:
        break;
    }
  }

  if (role == TextFieldRole) {
    properties.addItem(
        createProperty(AXWidgetAttributesEnum::Multiline,
                       createBooleanValue(axObject.isMultiline())));
  }

  if (roleAllowsReadonly(role)) {
    properties.addItem(
        createProperty(AXWidgetAttributesEnum::Readonly,
                       createBooleanValue(axObject.isReadOnly())));
  }

  if (roleAllowsRequired(role)) {
    properties.addItem(
        createProperty(AXWidgetAttributesEnum::Required,
                       createBooleanValue(axObject.isRequired())));
  }

  if (roleAllowsSort(role)) {
  }

  if (axObject.isRange()) {
    properties.addItem(
        createProperty(AXWidgetAttributesEnum::Valuemin,
                       createValue(axObject.minValueForRange())));
    properties.addItem(
        createProperty(AXWidgetAttributesEnum::Valuemax,
                       createValue(axObject.maxValueForRange())));
    properties.addItem(
        createProperty(AXWidgetAttributesEnum::Valuetext,
                       createValue(axObject.valueDescription())));
  }
}
