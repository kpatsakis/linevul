static std::string selectionAsString(WebFrame* frame)
{
    return frame->selectionAsText().utf8();
}
