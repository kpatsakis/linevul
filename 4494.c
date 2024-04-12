QByteArray DBusHelperProxy::performAction(const QString &action, const QByteArray &callerID, QByteArray arguments)
{
    if (!responder) {
        return ActionReply::NoResponderReply().serialized();
    }

    if (!m_currentAction.isEmpty()) {
        return ActionReply::HelperBusyReply().serialized();
    }
         return ActionReply::HelperBusyReply().serialized();
     }
