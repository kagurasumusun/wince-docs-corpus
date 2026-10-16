/* ExtraDefines.h -- supplementary macro definitions
 * 25 unassigned macros
 * (0 function-like, 25 object-like)
 */
#ifndef _EXTRADEFINES_H_
#define _EXTRADEFINES_H_

#define DMA_AUTO_INIT 0x10 // Auto initialization mode
#define FRAMEBUFFER_PHYSADDR 0xdc000000 // Physical address of the frame buffer
#define FRAMEBUFFER_SIZE 0x00400000 // 4M of frame buffer
#define HARDWARE_TIME_SET_PROBLEM 1 __int64 RealTimeBias;
#define IDC_FONTLIST 1000 // Control identifier of the list box
#define LDRFL_ADDR_VALID 0x0002 // Set if EdbgAddr member is valid.
#define LDRFL_JUMPIMG 0x0004 // If set, do not communicate with Eshell
#define LDRFL_USE_EDBG 0x0001 // Set to attempt to use debug Ethernet.
#define MBX_BYTE_MSG_SIZE 8 // 2 DWORDS
#define MBX_DWORD_MSG_SIZE 2 // 2 DWORDS
#define MEMORY_MAPPED_FILE_SIZE 0x10000 // 1 Mb
#define MONITOR_AREA 0x0000 // Use entire area of screen.
#define MONITOR_CENTER 0x0001 // Center rectangle on screen.
#define MONITOR_CLIP 0x0000 // Clip rectangle to screen.
#define MONITOR_WORKAREA 0x0002 // Use work area of screen.
#define READ_TRANSFER 0x01 // Read from the device.
#define UNIMDM_OPT_BAUDRATE 1 // use CBR_* values from Winbase.h
#define UNIMDM_OPT_DIALMOD 9 // dial modifier (dwValue is a LPCWSTR)
#define UNIMDM_OPT_MDMOPTIONS 6 // use MDM_* values from Mcx.h
#define UNIMDM_OPT_PARITY 3 // use values from Winbase.h
#define UNIMDM_OPT_STOPBITS 4 // use values from Winbase.h
#define UNIMDM_OPT_TERMOPTIONS 8 // use NETUI_LCD_TRMOPT_* values from Netui.h
#define UNIMDM_OPT_TIMEOUT 7 // call setup fail timer in seconds
#define UNIMDM_OPT_WAITBONG 5 // Seconds to wait for prompt tone
#define WRITE_TRANSFER 0x02 // Write to the device.
#endif /* _EXTRADEFINES_H_ */
