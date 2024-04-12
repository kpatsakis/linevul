V8Proxy* V8Proxy::retrieve(Frame* frame)
{
    return frame ? frame->script()->proxy() : 0;
}
