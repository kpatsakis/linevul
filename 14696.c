const SecurityOrigin* Document::topOrigin() const
{
    return topDocument()->securityOrigin();
}
