	__releases(key_serial_lock)
{
	spin_unlock(&key_serial_lock);
}
