/* wincon.h -- Windows CE unified surface
 *
 * ONE tree for every CE generation.  Version differences use
 * #if defined(_WIN32_WCE) && (_WIN32_WCE >= NNN) branches.
 * Win32-shared entries are marked 'win32-ref'.
 * Generated from wince-docs-corpus knowledge/ by
 * tools/gen-include-def.py --unified.
 * 49 constants, 0 declarations, 0 outlines, 0 base types, 0 extra macros, 0 extra decls
 */
#ifndef _WINCON_
#define _WINCON_


/* ==================================================================
 * constants (one evidence comment per #define; the
 * #if of a batch covers every #define in it; values
 * that differ per generation pool into #if/#elif
 * chains with the evidence after the #endif)
 * ================================================================ */
#define ATTACH_PARENT_PROCESS ((DWORD)-1)
#define BACKGROUND_BLUE 16
#define BACKGROUND_GREEN 32
#define BACKGROUND_INTENSITY 128
#define BACKGROUND_RED 64
#define CAPSLOCK_ON 128
#define CONSOLE_FULLSCREEN_MODE 1
#define CONSOLE_WINDOWED_MODE 2
#define CTRL_BREAK_EVENT 1
#define CTRL_C_EVENT 0
#define CTRL_CLOSE_EVENT 2
#define CTRL_LOGOFF_EVENT 5
#define CTRL_SHUTDOWN_EVENT 6
#define DOUBLE_CLICK 2
#define ENABLE_AUTO_POSITION 256
#define ENABLE_ECHO_INPUT 4
#define ENABLE_EXTENDED_FLAGS 128
#define ENABLE_INSERT_MODE 32
#define ENABLE_LINE_INPUT 2
#define ENABLE_MOUSE_INPUT 16
#define ENABLE_PROCESSED_INPUT 1
#define ENABLE_PROCESSED_OUTPUT 1
#define ENABLE_QUICK_EDIT_MODE 64
#define ENABLE_WINDOW_INPUT 8
#define ENABLE_WRAP_AT_EOL_OUTPUT 2
#define ENHANCED_KEY 256
#define FOCUS_EVENT 16
#define FOREGROUND_BLUE 1
#define FOREGROUND_GREEN 2
#define FOREGROUND_INTENSITY 8
#define FOREGROUND_RED 4
#define FROM_LEFT_1ST_BUTTON_PRESSED 1
#define FROM_LEFT_2ND_BUTTON_PRESSED 4
#define FROM_LEFT_3RD_BUTTON_PRESSED 8
#define FROM_LEFT_4TH_BUTTON_PRESSED 16
#define KEY_EVENT 1
#define LEFT_ALT_PRESSED 2
#define LEFT_CTRL_PRESSED 8
#define MENU_EVENT 8
#define MOUSE_EVENT 2
#define MOUSE_MOVED 1
#define MOUSE_WHEELED 4
#define NUMLOCK_ON 32
#define RIGHT_ALT_PRESSED 1
#define RIGHT_CTRL_PRESSED 4
#define RIGHTMOST_BUTTON_PRESSED 2
#define SCROLLLOCK_ON 64
#define SHIFT_PRESSED 16
#define WINDOW_BUFFER_SIZE_EVENT 4

#endif /* _WINCON_ */
