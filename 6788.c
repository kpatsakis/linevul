void BaseShadow::removeJob( const char* reason )
{
	this->removeJobPre(reason);
	
	DC_Exit( JOB_SHOULD_REMOVE );
}
