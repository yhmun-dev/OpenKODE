#include <config.h>
#include <KD/kd.h>

KD_API KDint KD_APIENTRY kdNameLookup(KDint af, const KDchar *hostname, void *eventuserptr)
{
    return 0;
}

KD_API void KD_APIENTRY kdNameLookupCancel(void *eventuserptr)
{
}

KD_API KDSocket *KD_APIENTRY kdSocketCreate(KDint type, void *eventuserptr)
{
    return KD_NULL;
}

KD_API KDint KD_APIENTRY kdSocketClose(KDSocket *socket)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdSocketBind(KDSocket *socket, const struct KDSockaddr *addr, KDboolean reuse)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdSocketGetName(KDSocket *socket, struct KDSockaddr *addr)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdSocketConnect(KDSocket *socket, const KDSockaddr *addr)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdSocketListen(KDSocket *socket, KDint backlog)
{
    return 0;
}

KD_API KDSocket *KD_APIENTRY kdSocketAccept(KDSocket *socket, KDSockaddr *addr, void *eventuserptr)
{
    return KD_NULL;
}

KD_API KDint KD_APIENTRY kdSocketSend(KDSocket *socket, const void *buf, KDint len)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdSocketSendTo(KDSocket *socket, const void *buf, KDint len, const KDSockaddr *addr)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdSocketRecv(KDSocket *socket, void *buf, KDint len)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdSocketRecvFrom(KDSocket *socket, void *buf, KDint len, KDSockaddr *addr)
{
    return 0;
}

KD_API KDuint32 KD_APIENTRY kdHtonl(KDuint32 hostlong)
{
    return 0;
}

KD_API KDuint16 KD_APIENTRY kdHtons(KDuint16 hostshort)
{
    return 0;
}

KD_API KDuint32 KD_APIENTRY kdNtohl(KDuint32 netlong)
{
    return 0;
}

KD_API KDuint16 KD_APIENTRY kdNtohs(KDuint16 netshort)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdInetAton(const KDchar *cp, KDuint32 *inp)
{
    return 0;
}

KD_API const KDchar *KD_APIENTRY kdInetNtop(KDuint af, const void *src, KDchar *dst, KDsize cnt)
{
    return KD_NULL;
}
