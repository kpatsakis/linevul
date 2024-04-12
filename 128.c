bool Document::allowExecutingScripts(Node* node)
{
    if (!frame() && !import())
        return false;
    if (!node->document().frame() && !node->document().import())
        return false;
    if (!contextDocument().get()->frame()->script()->canExecuteScripts(AboutToExecuteScript))
        return false;
    return true;
}
