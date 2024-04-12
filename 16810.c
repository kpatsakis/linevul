std::string GenerateUserAgent()
{
	srand((unsigned int)time(NULL));
	int cversion = rand() % 0xFFFF;
	int mversion = rand() % 3;
	int sversion = rand() % 3;
	std::stringstream sstr;
	sstr << "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/" << (601 + sversion) << "." << (36+mversion) << " (KHTML, like Gecko) Chrome/" << (53 + mversion) << ".0." << cversion << ".0 Safari/" << (601 + sversion) << "." << (36+sversion);
	return sstr.str();
}
