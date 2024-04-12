void DocumentLoader::stopLoadingForPolicyChange()
{
    ResourceError error = interruptedForPolicyChangeError();
    error.setIsCancellation(true);
    cancelMainResourceLoad(error);
}
