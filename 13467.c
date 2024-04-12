void HTMLElement::parseAttribute(const Attribute& attribute)
{
    if (isIdAttributeName(attribute.name()) || attribute.name() == classAttr || attribute.name() == styleAttr)
        return StyledElement::parseAttribute(attribute);

    if (attribute.name() == dirAttr)
        dirAttributeChanged(attribute);
    else if (attribute.name() == tabindexAttr) {
        int tabindex = 0;
        if (attribute.isEmpty())
            clearTabIndexExplicitly();
        else if (parseHTMLInteger(attribute.value(), tabindex)) {
            setTabIndexExplicitly(max(static_cast<int>(std::numeric_limits<short>::min()), min(tabindex, static_cast<int>(std::numeric_limits<short>::max()))));
        }
#if ENABLE(MICRODATA)
    } else if (attribute.name() == itempropAttr) {
        setItemProp(attribute.value());
    } else if (attribute.name() == itemrefAttr) {
        setItemRef(attribute.value());
    } else if (attribute.name() == itemtypeAttr) {
        setItemType(attribute.value());
#endif
    }
    else if (attribute.name() == onclickAttr) {
        setAttributeEventListener(eventNames().clickEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == oncontextmenuAttr) {
        setAttributeEventListener(eventNames().contextmenuEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == ondblclickAttr) {
        setAttributeEventListener(eventNames().dblclickEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onmousedownAttr) {
        setAttributeEventListener(eventNames().mousedownEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onmousemoveAttr) {
        setAttributeEventListener(eventNames().mousemoveEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onmouseoutAttr) {
        setAttributeEventListener(eventNames().mouseoutEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onmouseoverAttr) {
        setAttributeEventListener(eventNames().mouseoverEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onmouseupAttr) {
        setAttributeEventListener(eventNames().mouseupEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onmousewheelAttr) {
        setAttributeEventListener(eventNames().mousewheelEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onfocusAttr) {
        setAttributeEventListener(eventNames().focusEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onfocusinAttr) {
        setAttributeEventListener(eventNames().focusinEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onfocusoutAttr) {
        setAttributeEventListener(eventNames().focusoutEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onblurAttr) {
        setAttributeEventListener(eventNames().blurEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onkeydownAttr) {
        setAttributeEventListener(eventNames().keydownEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onkeypressAttr) {
        setAttributeEventListener(eventNames().keypressEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onkeyupAttr) {
        setAttributeEventListener(eventNames().keyupEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onscrollAttr) {
        setAttributeEventListener(eventNames().scrollEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onbeforecutAttr) {
        setAttributeEventListener(eventNames().beforecutEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == oncutAttr) {
        setAttributeEventListener(eventNames().cutEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onbeforecopyAttr) {
        setAttributeEventListener(eventNames().beforecopyEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == oncopyAttr) {
        setAttributeEventListener(eventNames().copyEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onbeforepasteAttr) {
        setAttributeEventListener(eventNames().beforepasteEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onpasteAttr) {
        setAttributeEventListener(eventNames().pasteEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == ondragenterAttr) {
        setAttributeEventListener(eventNames().dragenterEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == ondragoverAttr) {
        setAttributeEventListener(eventNames().dragoverEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == ondragleaveAttr) {
        setAttributeEventListener(eventNames().dragleaveEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == ondropAttr) {
        setAttributeEventListener(eventNames().dropEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == ondragstartAttr) {
        setAttributeEventListener(eventNames().dragstartEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == ondragAttr) {
        setAttributeEventListener(eventNames().dragEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == ondragendAttr) {
        setAttributeEventListener(eventNames().dragendEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onselectstartAttr) {
        setAttributeEventListener(eventNames().selectstartEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onsubmitAttr) {
        setAttributeEventListener(eventNames().submitEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onerrorAttr) {
        setAttributeEventListener(eventNames().errorEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onwebkitanimationstartAttr) {
        setAttributeEventListener(eventNames().webkitAnimationStartEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onwebkitanimationiterationAttr) {
        setAttributeEventListener(eventNames().webkitAnimationIterationEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onwebkitanimationendAttr) {
        setAttributeEventListener(eventNames().webkitAnimationEndEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onwebkittransitionendAttr) {
        setAttributeEventListener(eventNames().webkitTransitionEndEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == oninputAttr) {
        setAttributeEventListener(eventNames().inputEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == oninvalidAttr) {
        setAttributeEventListener(eventNames().invalidEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == ontouchstartAttr) {
        setAttributeEventListener(eventNames().touchstartEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == ontouchmoveAttr) {
        setAttributeEventListener(eventNames().touchmoveEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == ontouchendAttr) {
        setAttributeEventListener(eventNames().touchendEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == ontouchcancelAttr) {
        setAttributeEventListener(eventNames().touchcancelEvent, createAttributeEventListener(this, attribute));
#if ENABLE(FULLSCREEN_API)
    } else if (attribute.name() == onwebkitfullscreenchangeAttr) {
        setAttributeEventListener(eventNames().webkitfullscreenchangeEvent, createAttributeEventListener(this, attribute));
    } else if (attribute.name() == onwebkitfullscreenerrorAttr) {
        setAttributeEventListener(eventNames().webkitfullscreenerrorEvent, createAttributeEventListener(this, attribute));
#endif
    }
}
