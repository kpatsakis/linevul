bool NPJSObject::NP_HasProperty(NPObject* npObject, NPIdentifier propertyName)
{
    return toNPJSObject(npObject)->hasProperty(propertyName);
}
