bool Document::isPrivilegedContext(String& errorMessage, const PrivilegeContextCheck privilegeContextCheck) const
{
    if (securityContext().isSandboxed(SandboxOrigin)) {
        if (!SecurityOrigin::create(url())->isPotentiallyTrustworthy(errorMessage))
            return false;
    } else {
        if (!securityOrigin()->isPotentiallyTrustworthy(errorMessage))
            return false;
    }

    if (privilegeContextCheck == StandardPrivilegeCheck) {
        Document* context = parentDocument();
        while (context) {
            if (!context->isSrcdocDocument()) {
                if (context->securityContext().isSandboxed(SandboxOrigin)) {
                    RefPtr<SecurityOrigin> origin = SecurityOrigin::create(context->url());
                    if (!origin->isPotentiallyTrustworthy(errorMessage))
                        return false;
                } else {
                    if (!context->securityOrigin()->isPotentiallyTrustworthy(errorMessage))
                        return false;
                }
            }
            context = context->parentDocument();
        }
    }
    return true;
}
