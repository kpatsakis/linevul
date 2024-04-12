static bool NPN_GetProperty(NPP, NPObject* npObject, NPIdentifier propertyName, NPVariant* result)
{
    if (npObject->_class->hasProperty && npObject->_class->getProperty) {
        if (npObject->_class->hasProperty(npObject, propertyName))
            return npObject->_class->getProperty(npObject, propertyName, result);
    }
    
    VOID_TO_NPVARIANT(*result);
    return false;
}
