#include <config.h>
#include <KD/ATX_bluetooth.h>

KD_API KDint KD_APIENTRY kdBtInquireDevicesATX(KDBtLocalDeviceATX *localdevice, KDint access, void *eventuserptr)
{
    return 0;
}

KD_API void KD_APIENTRY kdBtCancelInquireDevicesATX(void *eventuserptr)
{
}

KD_API KDint KD_APIENTRY kdBtGetFriendlyNameATX(KDBtLocalDeviceATX *localdevice, const KDBdAddrATX *bdaddr, void *eventuserptr)
{
    return 0;
}

KD_API void KD_APIENTRY kdBtCancelGetFriendlyNameATX(void *eventuserptr)
{
}

KD_API KDint KD_APIENTRY kdBtSearchServicesATX(KDBtLocalDeviceATX *localdevice, const KDBdAddrATX *bdaddr, const KDint32 *attrset, const KDUuidATX *uuidset, void *eventuserptr)
{
    return 0;
}

KD_API void KD_APIENTRY kdBtCancelSearchServicesATX(void *eventuserptr)
{
}

KD_API KDint KD_APIENTRY kdBtServiceRecordGetRfcommChannelATX(KDBtServiceRecordATX *servicerecord)
{
    return 0;
}

KD_API void KD_APIENTRY kdBtServiceRecordFreeATX(KDBtServiceRecordATX *servicerecord)
{
}

KD_API KDBtServiceRecordATX *KD_APIENTRY kdBtServiceRecordCreateRfcommATX(const KDUuidATX *uuid, KDint channel)
{
    return KD_NULL;
}

KD_API KDint KD_APIENTRY kdBtRegisterServiceATX(KDBtLocalDeviceATX *localdevice, KDBtServiceRecordATX *servicerecord)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdBtSocketSetFlagsATX(KDSocket *socket, KDuint flags)
{
    return 0;
}

KD_API KDint KD_APIENTRY kdBtSetDiscoverableATX(KDBtLocalDeviceATX *localdevice, KDuint mode)
{
    return 0;
}
