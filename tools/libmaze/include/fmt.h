#ifndef FMT_H
#define FMT_H

#include "core.h"

#ifdef __cplusplus
extern "C" {
#endif 

LM_Grid* fmt_gen(LM_Maze*, int);
int fmt_mod(LM_Grid*, int);
int fmt_space(LM_Grid*, int);

#ifdef __cplusplus
}
#endif

#endif /* FMT_H */