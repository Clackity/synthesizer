/* defines nfilter::cdelay class */

#pragma once

#include <memory.h>

namespace nfilter {
	class cdelay : public cfilter {
		protected:
			double *line;
			int len;
			int cursor;

		public:
			cdelay() {
				line = 0;
				len = 0;
				cursor = 0;
			}

			virtual ~cdelay() {
				free();
			}

			virtual void filter (
				double *dest
				,const double *src
				,const int len
			) {
				if (!line) return;
				for (int i = 0; i < len; ++i) {
					double a = src[i];
					dest[i] = line[cursor];
					line[cursor++] = a;
					cursor = cursor == this->len ? 0 : cursor;
				}
			}

			virtual int getdelay() {
				return line ? len : 0;
			}

			void free() {
				delete line;
				line = 0;
			}

			void set(int len) {
				free();
				if (len < 1) len = 1;
				if ((line = (double*)calloc(len, sizeof(double)))) {
					this->len = len;
					cursor = 0;
				}
			}
	};
}