status_t OMX::getGraphicBufferUsage(
        node_id node, OMX_U32 port_index, OMX_U32* usage) {
 return findInstance(node)->getGraphicBufferUsage(port_index, usage);
}
