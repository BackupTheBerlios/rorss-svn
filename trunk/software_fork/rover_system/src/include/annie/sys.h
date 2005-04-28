/**
 * $Id: sys.h,v 1.1 2004/06/16 10:53:30 opx Exp $
 * @author OP
 */

#ifndef SYS_H
#define SYS_H

#include "defines.h"

namespace annie
{
/// system dependent. May install some goodies like segfault handler, so
/// better call it prior to anything else
void sysInit();
}

#endif
