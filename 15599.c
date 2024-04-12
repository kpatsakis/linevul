PassRefPtr<Comment> Document::createComment(const String& data)
{
    return Comment::create(*this, data);
}
