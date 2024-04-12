Action::AuthStatus Polkit1Backend::authorizeAction(const QString &action)
{
    Q_UNUSED(action)
    return Action::AuthorizedStatus;
}
