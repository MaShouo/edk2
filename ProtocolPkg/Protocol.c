/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2025-11-13 17:33:10
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2025-11-16 22:18:58
 * @FilePath: /edk2/ProtocolPkg/Protocol.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>

EFI_STATUS
EFIAPI
UefiMain(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN NoHandles = 0;
    EFI_HANDLE *Buffer = NULL;
    Status = gBS->LocateHandleBuffer(
        ByProtocol,
        &gEfiGraphicsOutputProtocolGuid,
        NULL,
        &NoHandles,
        &Buffer
    );
    
    DEBUG((DEBUG_INFO, "Hello, this is an INFO message.\n"));
    Print(L"Status: %r\n", Status);

    if(EFI_ERROR(Status))
    {
        Print(L"LocateHandleBuffer failed: %r\n", Status);
        return Status;
    }
    
    Print(L"Hello, UEFI World!\n");
    Print(L"NoHandles: %d\n", NoHandles);

    EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop;
    Status = gBS->OpenProtocol(
        Buffer[0],
        &gEfiGraphicsOutputProtocolGuid,
        (VOID **)&Gop,
        ImageHandle,
        NULL,
        EFI_OPEN_PROTOCOL_GET_PROTOCOL
    );
    Print(L"OpenProtocol Status: %r\n", Status);
    if(EFI_ERROR(Status))
    {
        Print(L"OpenProtocol failed: %r\n", Status);
        return Status;
    }

    return Status;
}