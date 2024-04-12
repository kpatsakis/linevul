static void drm_mode_object_put(struct drm_device *dev,
				struct drm_mode_object *object)
{
	mutex_lock(&dev->mode_config.idr_mutex);
	idr_remove(&dev->mode_config.crtc_idr, object->id);
	mutex_unlock(&dev->mode_config.idr_mutex);
}
