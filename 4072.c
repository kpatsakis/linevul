status_t OMX::updateGraphicBufferInMeta(
        node_id node, OMX_U32 port_index,
 const sp<GraphicBuffer> &graphicBuffer, buffer_id buffer) {
 return findInstance(node)->updateGraphicBufferInMeta(
            port_index, graphicBuffer, buffer);
}
