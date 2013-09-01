/* defines nlowlevel::sin functions

seems to work!

description:
	sin (
		double *dest                  // destination array
		,const int len                // length of dest
		,const double rrate           // 1.0 / samples_per_second
		,const double mag             // magnitude of result
		,const double freq | *freq    // scalar or array of frequency values, in hertz
		,[double &phase |             // starting phase value, reuse next time
			[const double *phase        // array of phase values
			,double &acc]]              // set to 0.0 to start, reuse next time
	);

*/

#pragma once

#include "constants.h"

#include <math.h>

namespace nlowlevel {
	namespace {
		double sine1fast(double x) { // there might be a way to make this faster, but the compiler already does well here
			x = (x - floor(x)) * 2.0 - 1.0; // wrap to [-1..1]
			x *= -4.0 * (1.0 - abs(x));
			const double P = 0.225; // 0.225, 0.218
			const double Q = 0.775; // 0.775, 0.782
			//return x * (P * (abs(x) - 1.0) + 1.0); // low precision
			return x * (Q + P * abs(x)); // high precision
		}
	}

	void sin ( // a a
		double *dest
		,const int len
		,const double rrate
		,const double mag
		,const double *freq
		,const double *phase
		,double &acc
	) {
		for (int i = 0; i < len; ++i) {
			acc += freq[i] * rrate;
			dest[i] = mag * sine1fast(phase[i] + acc);
		}
	}

	void sin ( // a s
		double *dest
		,const int len
		,const double rrate
		,const double mag
		,const double *freq
		,double &phase
	) {
		for (int i = 0; i < len; ++i) {
			dest[i] = mag * sine1fast((phase += freq[i] * rrate));
		}
	}

	void sin ( // s a
		double *dest
		,const int len
		,const double rrate
		,const double mag
		,const double freq
		,const double *phase
		,double &acc
	) {
		for (int i = 0; i < len; ++i) {
			acc += freq * rrate;
			dest[i] = mag * sine1fast(phase[i] + acc);
		}
	}

	void sin ( // s s
		double *dest
		,const int len
		,const double rrate
		,const double mag
		,const double freq
		,double &phase
	) {
		for (int i = 0; i < len; ++i) {
			dest[i] = mag * sine1fast((phase += freq * rrate));
		}
	}
}