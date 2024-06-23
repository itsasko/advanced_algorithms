#ifndef KMP_H
#define KMP_H
#include <string>
#include <vector>
#include <unordered_set>

class KMP
{
public:
	KMP(std::string _pat, std::string _txt);
	void prefix_length();
	std::vector<int> occurences;
	void search();
private:
	std::string pat, txt;
	std::vector<int> lps;
};
#endif
