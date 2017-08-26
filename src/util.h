#pragma once

#include <string>

using namespace std;

namespace Util
{
	namespace random
	{
		int ascii();
	};
	
	namespace math
	{
		unsigned levenshtein(const string& s1, const string& s2);
	};
};

