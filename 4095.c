bool Document::isSecureContext(String& errorMessage, const SecureContextCheck privilegeContextCheck) const
{
    if (isSecureContextImpl(privilegeContextCheck))
        return true;
    errorMessage = SecurityOrigin::isPotentiallyTrustworthyErrorMessage();
    return false;
}
