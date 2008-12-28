/* Copyright (c) 2008 Peter Palotas
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 */
#pragma once

/*
VSS requesters, writers, and providers compiled for 		Will run on
--------------------------------------------------------------------------------------------------------------------------------------------------
Windows Server 2008 (64-bit) and Windows Vista (64-bit) 	Windows Server 2008 (64-bit) and Windows Vista (64-bit)

Windows Server 2008 (32-bit) and Windows Vista (32-bit) 	Windows Server 2008 (32-bit) and Windows Vista (32-bit)

Windows Server 2003 (64-bit) 								Windows Server 2008 (64-bit), Windows Vista (64-bit), and Windows Server 2003 (64-bit)

Windows Server 2003 (32-bit) 								Windows Server 2008 (32-bit), Windows Vista (32-bit), and Windows Server 2003 (32-bit)
															Note  Requesters will also run on Windows Server 2003 (64-bit).

Windows XP 64-Bit Edition 									Windows Server 2003 (64-bit) and Windows XP 64-Bit Edition

Windows XP (32-bit) 										Windows XP (32-bit)
															Note  Requesters will also run on Windows XP 64-Bit Edition.
*/
/*
	Windows Server 2008								NTDDI_WS08
	Windows Vista with Service Pack 1 (SP1)			NTDDI_VISTASP1
	Windows Vista									NTDDI_VISTA
	Windows Server 2003 with Service Pack 1 (SP1)	NTDDI_WS03SP1
	Windows Server 2003								NTDDI_WS03
	Windows XP with Service Pack 2 (SP2)			NTDDI_WINXPSP2
	Windows XP with Service Pack 1 (SP1)			NTDDI_WINXPSP1
	Windows XP										NTDDI_WINXP
*/


#define ALPHAVSS_TARGET_WINXP		0x0400
#define ALPHAVSS_TARGET_WIN2003		0x0500
#define ALPHAVSS_TARGET_WIN2008		0x0600

#ifndef ALPHAVSS_TARGET
#error "ALPHAVSS_TARGET must be defined"
#endif

#if ALPHAVSS_TARGET == ALPHAVSS_TARGET_WINXP

#define NTDDI_VERSION NTDDI_WINXPSP2
#define _WIN32_WINNT _WIN32_WINNT_WINXP
#define WINVER _WIN32_WINNT

#elif ALPHAVSS_TARGET == ALPHAVSS_TARGET_WIN2003

#define NTDDI_VERSION NTDDI_WS03SP1
#define _WIN32_WINNT _WIN32_WINNT_WS03
#define WINVER 0x501

#elif ALPHAVSS_TARGET == ALPHAVSS_TARGET_WIN2008

#define NTDDI_VERSION NTDDI_WS08
#define _WIN32_WINNT _WIN32_WINNT_WS08
#define WINVER _WIN32_WINNT

#else
#error "ALPHAVSS_TARGET has unrecognized value"
#endif
