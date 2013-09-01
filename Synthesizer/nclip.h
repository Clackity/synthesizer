/* defines namespace nclip */

#pragma once

#include "nlowlevel.h"
#include "nregister.h"

namespace nclip {
	union uacc {
		double d;
	};
}

#include "nclip.dispatch.h"

namespace nclip {
	void clip (
		const double start
		//,const double rate
		//,const double rrate
		,const ninstruction::sinst &inst
		,uacc &acc
	) {
		if (inst.start + inst.len <= start) return;
		if (inst.start > start + nregister::duration) return;
		if (inst.start < start) {
			if (inst.start + inst.len < start + nregister::duration) {
				fbclip[inst.opcode](start, inst, acc);
			} else {
				fclip[inst.opcode](start, inst, acc);
			}
		} else if (inst.start + inst.len <= start + nregister::duration) {
			fnoclip[inst.opcode](start, inst);
		} else {
			feclip[inst.opcode](start, inst, acc);
		}
	}
}