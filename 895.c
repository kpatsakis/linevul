static int in_close_pcm_devices(struct stream_in *in)
{
 struct pcm_device *pcm_device;
 struct listnode *node;
 struct audio_device *adev = in->dev;

    list_for_each(node, &in->pcm_dev_list) {
        pcm_device = node_to_item(node, struct pcm_device, stream_list_node);
 if (pcm_device) {
 if (pcm_device->pcm)
                pcm_close(pcm_device->pcm);
            pcm_device->pcm = NULL;
 if (pcm_device->sound_trigger_handle > 0)
                adev->sound_trigger_close_for_streaming(
                        pcm_device->sound_trigger_handle);
            pcm_device->sound_trigger_handle = 0;
 }
 }
 return 0;
}
