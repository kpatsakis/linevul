void DocumentThreadableLoader::responseReceived(Resource* resource, const ResourceResponse& response, PassOwnPtr<WebDataConsumerHandle> handle)
{
    ASSERT_UNUSED(resource, resource == this->resource());
    ASSERT(m_async);

    if (handle)
        m_isUsingDataConsumerHandle = true;

    handleResponse(resource->identifier(), response, std::move(handle));
}
