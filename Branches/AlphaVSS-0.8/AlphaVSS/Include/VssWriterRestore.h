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

#include <vss.h>

namespace Alphaleonis { namespace Win32 { namespace Vss
{
	/// <summary>The <see cref="VssWriterRestore"/> enumeration is used by a writer to indicate to a requester the conditions under which it will handle events generated during a restore operation.</summary>
	public enum class VssWriterRestore
	{
		/// <summary>
		/// 	<para>It is not known whether the writer will perform special operations during the restore operation.</para>
		/// 	<para>This state indicates a writer error.</para>
		/// </summary>
		Undefined = VSS_WRE_UNDEFINED,

		/// <summary>The writer does not require restore events.</summary>
		Never = VSS_WRE_NEVER,

		/// <summary>
		/// 	Indicates that the writer always expects to handle a <c>PreRestore</c> event, but expects to handle a 
		/// 	<c>PostRestore</c> event only if a restore fails when implementing either a 
		/// 	<see dref="F:Alphaleonis.Win32.Vss.VssRestoreMethod.RestoreIfNotThere"/> or
		/// 	<see dref="F:Alphaleonis.Win32.Vss.VssRestoreMethod.RestoreIfCanReplace"/> restore method (<see dref="T:Alphaleonis.Win32.Vss.VssRestoreMethod"/>)
		/// </summary>
		IfReplaceFails = VSS_WRE_IF_REPLACE_FAILS,

		/// <summary>The writer always performs special operations during the restore operation.</summary>
		Always = VSS_WRE_ALWAYS
	};
}
} }