ReadUserLogState::SetScoreFactor( enum ScoreFactors which, int factor )
{
	switch ( which )
	{
	case SCORE_CTIME:
		m_score_fact_ctime = factor;
		break;
	case SCORE_INODE:
		m_score_fact_inode = factor;
		break;
	case SCORE_SAME_SIZE:
		m_score_fact_same_size = factor;
		break;
	case SCORE_GROWN:
		m_score_fact_grown = factor;
		break;
	case SCORE_SHRUNK:
		m_score_fact_shrunk = factor;
		break;
	default:
		break;
	}
	Update();
}
