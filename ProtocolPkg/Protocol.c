/*
 * @Author: MaShouo 1324062363@qq.com
 * @Date: 2025-11-13 17:33:10
 * @LastEditors: MaShouo 1324062363@qq.com
 * @LastEditTime: 2025-11-21 20:03:06
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

    UINTN SizeOfInfo = 0;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
    for(UINTN i = 0; i < Gop->Mode->MaxMode; i++)
    {
        Status = Gop->QueryMode(
        Gop,
        i,
        &SizeOfInfo,
        &Info
        );

        if(EFI_ERROR(Status))
        {
            Print(L"QueryMode %d failed: %r\n", i, Status);
            return Status;
        }
        Print(L"Mode %d, H = %d, V=%d.\n",
             i,
             Info->HorizontalResolution,
             Info->VerticalResolution);
    }

    Status = Gop -> SetMode(Gop, 22);
    if(EFI_ERROR(Status))
    {
        Print(L"SetMode failed: %r\n", Status);
        return Status;
    }

    return Status;
}