/* defines namespace nregister

usage:
	Must call init() once per thread.

*/

#pragma once

namespace nregister {
	const int len = 1024;
	const int num = 8;

	double rate;
	double rrate;
	double duration;

	__declspec(thread) double localreg[num][len];
}