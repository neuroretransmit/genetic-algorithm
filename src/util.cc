#include "util.h"

#include <algorithm>
#include <vector>

int Util::random::ascii()
{
	return ' ' + rand() % (' ' - '~' + 1);
}

unsigned Util::math::levenshtein(const string& s1, const string& s2)
{
	const size_t len1 = s1.size(), len2 = s2.size();
	vector<unsigned> col(len2 + 1), prev_col(len2 + 1);

	for (unsigned i = 0; i < prev_col.size(); i++)
		prev_col[i] = i;

	for (unsigned i = 0; i < len1; i++) {
		col[0] = i + 1;

		for (unsigned j = 0; j < len2; j++)
			col[j + 1] = min( { prev_col[1 + j] + 1, col[j] + 1, prev_col[j] + (s1[i] == s2[j] ? 0 : 1) });

		col.swap(prev_col);
	}

	return prev_col[len2];
}

