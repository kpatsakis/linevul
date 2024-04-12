void AudioParam::connect(AudioNodeOutput* output)
{
    ASSERT(context()->isGraphOwner());

    ASSERT(output);
    if (!output)
        return;

    if (m_outputs.contains(output))
        return;

    output->addParam(this);
    m_outputs.add(output);
    changedOutputs();
}
