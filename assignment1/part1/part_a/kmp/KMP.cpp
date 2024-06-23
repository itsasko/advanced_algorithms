#ifndef KMP_CPP
#define KMP_CPP
#include "KMP.h"

KMP::KMP(std::string _pat, std::string _txt) : pat(_pat), txt(_txt) {}

void KMP::prefix_length() {
	int M = pat.size();
	lps.resize(M, 0);
	int length = 0;
	int i = 1;

	while (i < M) {
		if (pat[i] == pat[length]) {
			length++;
			lps[i] = length;
			i++;
		}
		else {
			if (length != 0) {
				length = lps[length - 1];
			}
			else {
				lps[i] = 0;
				i++;
			}
		}
	}
}



void KMP::search() {
	prefix_length();

	int pat_c = 0;
	int txt_c = 0;

	while (txt_c < txt.size()) {
		if (pat[pat_c] == txt[txt_c]) {
			pat_c++;
			txt_c++;
		}

		if (pat_c == pat.size()) {
			occurences.push_back(txt_c - pat_c);
			pat_c = lps[pat_c - 1];
		}
		else if (txt_c < txt.size() && pat[pat_c] != txt[txt_c]) {
			if (pat_c != 0) {
				pat_c = lps[pat_c - 1];
			}
			else {
				txt_c++;
			}
		}
	}
}
#endif