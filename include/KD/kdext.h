#ifndef __kdext_h_
#define __kdext_h_ 1

#ifdef __cplusplus
extern "C" {
#endif

KD_API KDint KD_APIENTRY kdInit(int argc, char *argv[]);

KD_API void KD_APIENTRY kdDeinit(void);

KD_API void *KD_APIENTRY kdCalloc(KDsize num, KDsize size);

#ifdef __cplusplus
}
#endif

#endif /* __kdext_h_ */
