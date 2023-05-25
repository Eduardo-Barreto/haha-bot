#ifndef __UTILS_H__
#define __UTILS_H__

#define abs(x) ((x) > 0 ? (x) : -(x))

#define max(x, y) ((x) > (y) ? (x) : (y))

#define min(x, y) ((x) < (y) ? (x) : (y))

#define constrain(v, x, y) ((v) < (x) ? (x) : ((v) > (y) ? (y) : (v)))

#define len(arr) (sizeof(arr) / sizeof(arr[0]))

#define map(x, in_min, in_max, out_min, out_max) ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)

#endif
