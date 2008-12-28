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

using namespace System;

namespace Alphaleonis { namespace Win32 { namespace Vss
{
	/// <summary>
	///	The <see cref="VssSnapshotCompatibility"/> enumeration indicates which volume control or file I/O operations are disabled for the 
	///	volume that has been shadow copied.</summary>
	[Flags]
	public enum class VssSnapshotCompatibility
	{
		/// <summary>None of the other flags.</summary>
		None = 0x00,
		/// <summary>The provider managing the shadow copies for a specified volume does not support defragmentation operations on that volume.</summary>
		DisableDefrag = VSS_SC_DISABLE_DEFRAG,
		/// <summary>The provider managing the shadow copies for a specified volume does not support content index operations on that volume.</summary>
		DisableContentIndex = VSS_SC_DISABLE_CONTENTINDEX 
	};

}
} }