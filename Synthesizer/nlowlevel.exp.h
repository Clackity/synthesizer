/* defines nlowlevel::exp functions

requires:
	<math.h>
	//<ipp.h>
	//have called init_intel()

description:
	exp *dest, len, *src

	dest[i] = exp(a[i])

*/

#pragma once

#include <math.h>

namespace nlowlevel {
	void exp (
		double *dest
		,const int len
		,const double *src
	) {
		for (int i = 0; i < len; ++i) {
			dest[i] = ::exp(src[i]);
		}
		//vdExp(len, src, dest);
	}
}		