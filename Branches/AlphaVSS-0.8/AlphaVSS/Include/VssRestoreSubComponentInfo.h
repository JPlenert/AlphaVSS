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

namespace Alphaleonis { namespace Win32 { namespace Vss 
{
	/// <summary>
	///		Represents information about a Subcomponent associated with a given component.
	/// </summary>
	public ref class VssRestoreSubcomponentInfo sealed
	{
	public:
		/// <summary>
		///     Initializes a new instance of <see cref="VssRestoreSubcomponentInfo" />.
		/// </summary>
		/// <param name="logicalPath">The logical path of the Subcomponent. This can not be empty when working with Subcomponents.</param>
		/// <param name="componentName">The name of the Subcomponent. This can not be empty.</param>
		VssRestoreSubcomponentInfo(String^ logicalPath, String^ componentName);

		/// <summary>The logical path of the Subcomponent. This can not be empty when working with Subcomponents.</summary>
		property String^ LogicalPath { String^ get(); }

		/// <summary>The name of the Subcomponent. This can not be empty.</summary>
		property String^ ComponentName { String^ get(); }
	private:
		String^ mLogicalPath;
		String^ mComponentName;
	};



} } }
