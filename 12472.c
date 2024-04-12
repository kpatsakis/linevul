int QQuickWebViewExperimental::schemeDelegates_Count(QDeclarativeListProperty<QQuickUrlSchemeDelegate>* property)
{
    return property->object->children().count();
}
