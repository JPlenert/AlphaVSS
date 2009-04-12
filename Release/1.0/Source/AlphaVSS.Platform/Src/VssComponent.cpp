/* Copyright (c) 2008-2009 Peter Palotas
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
#include "StdAfx.h"

#include "VssComponent.h"


namespace Alphaleonis { namespace Win32 { namespace Vss
{
	VssComponent^ VssComponent::Adopt(::IVssComponent *vssWriterComponents)
	{
		try
		{
			return gcnew VssComponent(vssWriterComponents);
		}
		catch (...)
		{
			vssWriterComponents->Release();
			throw;
		}
	}

	VssComponent::VssComponent(::IVssComponent *vssComponent)
		: mVssComponent(vssComponent), 
		mAlternateLocationMappings(nullptr),
		mDirectedTargets(nullptr),
#if ALPHAVSS_TARGET >= ALPHAVSS_TARGET_WIN2003
		mDifferencedFiles(nullptr),
#endif
		mRestoreSubcomponents(nullptr),
		mPartialFiles(nullptr),
		mNewTargets(nullptr)
	{
		mAlternateLocationMappings = gcnew AlternateLocationMappingList(this);
		mDirectedTargets = gcnew DirectedTargetList(this);
#if ALPHAVSS_TARGET >= ALPHAVSS_TARGET_WIN2003
		mDifferencedFiles = gcnew DifferencedFileList(this);
#endif
		mRestoreSubcomponents = gcnew RestoreSubcomponentList(this);
		mPartialFiles = gcnew PartialFileList(this);
		mNewTargets = gcnew NewTargetList(this);
	}

	VssComponent::~VssComponent()
	{
		this->!VssComponent();
	}

	VssComponent::!VssComponent()
	{
		if (mVssComponent != 0)
		{
			mVssComponent->Release();
			mVssComponent = 0;
		}

#ifdef ALPHAVSS_HAS_COMPONENTEX
		if (mIVssComponentEx != 0)
		{
			mIVssComponentEx->Release();
			mIVssComponentEx = 0;
		}
#endif
	}

#if 0
	void VssComponent::AddDifferencedFilesByLastModifyTime(String ^ path, String ^ fileSpec, bool recursive, DateTime lastModifyTime)
	{
		CheckCom(mVssComponent->AddDifferencedFilesByLastModifyTime(NoNullAutoMStr(path), 
			NoNullAutoMStr(fileSpec), recursive,ToFileTime(lastModifyTime)));
	}

	void VssComponent::AddDifferencedFilesByLastModifyTime(VssDifferencedFileInfo^ differencedFile)
	{
		AddDifferencedFilesByLastModifyTime(differencedFile->Path, differencedFile->FileSpec, differencedFile->IsRecursive, differencedFile->LastModifyTime);
	}

	void VssComponent::AddDirectedTarget(String ^ sourcePath, String^ sourceFileName, String^ sourceRangeList, String^ destinationPath, String^ destinationFileName, String^ destinationRangeList)
	{
		CheckCom(mVssComponent->AddDirectedTarget(
			NoNullAutoMStr(sourcePath), NoNullAutoMStr(sourceFileName), NoNullAutoMStr(sourceRangeList),
			NoNullAutoMStr(destinationPath), NoNullAutoMStr(destinationFileName), NoNullAutoMStr(destinationRangeList)));
	}

	void VssComponent::AddPartialFile(String^ path, String^ filename, String^ ranges, String^ metaData)
	{
		CheckCom(mVssComponent->AddPartialFile(NoNullAutoMStr(path), NoNullAutoMStr(filename), NoNullAutoMStr(ranges), AutoMStr(metaData)));
	}

	void VssComponent::AddDirectedTarget(VssDirectedTargetInfo ^directedTarget)
	{
		AddDirectedTarget(directedTarget->SourcePath, directedTarget->SourceFileName, directedTarget->SourceRangeList, 
			directedTarget->DestinationPath, directedTarget->DestinationFileName, directedTarget->DestinationRangeList);
	}

	void VssComponent::AddParitalFile(VssPartialFileInfo^ partialFile)
	{
		AddPartialFile(partialFile->Path, partialFile->FileName, partialFile->Range, partialFile->Metadata);
	}

	String^ VssComponent::BackupMetadata::get()
	{
		AutoBStr bstrBackupMetadata;
		CheckCom(mVssComponent->GetBackupMetadata(&bstrBackupMetadata));
		return bstrBackupMetadata;
	}

	String^ VssComponent::RestoreMetadata::get()
	{
		AutoBStr s;
		CheckCom(mVssComponent->GetRestoreMetadata(&s));
		return s;
	}

		void VssComponent::SetBackupMetadata(String^ metadata)
	{
		CheckCom(mVssComponent->SetBackupMetadata(NoNullAutoMStr(metadata)));
	}

	void VssComponent::SetBackupStamp(String^ stamp)
	{
		CheckCom(mVssComponent->SetBackupStamp(NoNullAutoMStr(stamp)));
	}


	void VssComponent::SetPostRestoreFailureMsg(String^ msg)
	{
		CheckCom(mVssComponent->SetPostRestoreFailureMsg(NoNullAutoMStr(msg)));
	}


	void VssComponent::SetPreRestoreFailureMsg(String^ msg)
	{
		CheckCom(mVssComponent->SetPreRestoreFailureMsg(NoNullAutoMStr(msg)));
	}


	void VssComponent::SetRestoreMetadata(String^ metadata)
	{
		CheckCom(mVssComponent->SetRestoreMetadata(NoNullAutoMStr(metadata)));
	}


	void VssComponent::SetRestoreTarget(VssRestoreTarget target)
	{
		CheckCom(mVssComponent->SetRestoreTarget((VSS_RESTORE_TARGET)target));
	}

#endif

	bool VssComponent::AdditionalRestores::get()
	{
		bool bAdditionalRestores;
		CheckCom(mVssComponent->GetAdditionalRestores(&bAdditionalRestores));
		return bAdditionalRestores;
	}

	String^ VssComponent::BackupOptions::get()
	{
		AutoBStr str;
		CheckCom(mVssComponent->GetBackupOptions(&str));
		return str;
	}

	String^ VssComponent::BackupStamp::get()
	{
		AutoBStr str;
		CheckCom(mVssComponent->GetBackupStamp(&str));
		return str;
	}

	bool VssComponent::BackupSucceeded::get()
	{
		bool b;
		CheckCom(mVssComponent->GetBackupSucceeded(&b));
		return b;
	}

	String^ VssComponent::ComponentName::get()
	{
		AutoBStr str;
		CheckCom(mVssComponent->GetComponentName(&str));
		return str;
	}

	VssComponentType VssComponent::ComponentType::get()
	{
		VSS_COMPONENT_TYPE type;
		CheckCom(mVssComponent->GetComponentType(&type));
		return (VssComponentType)type;
	}

	VssFileRestoreStatus VssComponent::FileRestoreStatus::get()
	{
		VSS_FILE_RESTORE_STATUS status;
		CheckCom(mVssComponent->GetFileRestoreStatus(&status));
		return (VssFileRestoreStatus)status;
	}

	String^ VssComponent::LogicalPath::get()
	{
		AutoBStr path;
		CheckCom(mVssComponent->GetLogicalPath(&path));
		return path;
	}

	String^ VssComponent::PostRestoreFailureMsg::get()
	{
		AutoBStr s;
		CheckCom(mVssComponent->GetPostRestoreFailureMsg(&s));
		return s;
	}

	String^ VssComponent::PreRestoreFailureMsg::get()
	{
		AutoBStr s;
		CheckCom(mVssComponent->GetPreRestoreFailureMsg(&s));
		return s;
	}

	String^ VssComponent::PreviousBackupStamp::get()
	{
		AutoBStr s;
		CheckCom(mVssComponent->GetPreviousBackupStamp(&s));
		return s;
	}

	String^ VssComponent::RestoreOptions::get()
	{
		AutoBStr s;
		CheckCom(mVssComponent->GetRestoreOptions(&s));
		return s;
	}

	VssRestoreTarget VssComponent::RestoreTarget::get()
	{
		VSS_RESTORE_TARGET tgt;
		CheckCom(mVssComponent->GetRestoreTarget(&tgt));
		return (VssRestoreTarget)tgt;
	}

	bool VssComponent::IsSelectedForRestore::get()
	{
		bool b;
		CheckCom(mVssComponent->IsSelectedForRestore(&b));
		return b;
	}


	IList<VssDirectedTargetInfo^>^ VssComponent::DirectedTargets::get()
	{
		return mDirectedTargets;
	}

	IList<VssPartialFileInfo^>^ VssComponent::PartialFiles::get()
	{
		return mPartialFiles;
	}

	IList<VssWMFileDescription^>^ VssComponent::NewTargets::get()
	{
		return mNewTargets;
	}

	IList<VssDifferencedFileInfo^>^ VssComponent::DifferencedFiles::get()
	{
#if ALPHAVSS_TARGET >= ALPHAVSS_TARGET_WIN2003
		return mDifferencedFiles;
#else
      throw gcnew NotSupportedException(Alphaleonis::Win32::Vss::Resources::LocalizedStrings::NotSupportedUntilWin2003);
#endif
	}


	IList<VssRestoreSubcomponentInfo^>^ VssComponent::RestoreSubcomponents::get()
	{
		return mRestoreSubcomponents;
	}

	IList<VssWMFileDescription^>^ VssComponent::AlternateLocationMappings::get()
	{
		return mAlternateLocationMappings;
	}


	//
	// DirectedTargetList
	//
	VssComponent::DirectedTargetList::DirectedTargetList(VssComponent^ component)
		: mComponent(component)
	{
	}

	int VssComponent::DirectedTargetList::Count::get()
	{
		if (mComponent->mVssComponent == 0)
			throw gcnew ObjectDisposedException("Instance of IList used after the object creating it was disposed.");

		UINT count;
		CheckCom(mComponent->mVssComponent->GetDirectedTargetCount(&count));
		return count;
	}

	VssDirectedTargetInfo^ VssComponent::DirectedTargetList::default::get(int index)
	{
		if (mComponent->mVssComponent == 0)
			throw gcnew ObjectDisposedException("Instance of IList used after the object creating it was disposed.");

		if (index < 0 || index >= Count)
			throw gcnew ArgumentOutOfRangeException("index");

		AutoBStr bsSourcePath, bsSourceFileName, bsSourceRangeList;
		AutoBStr bsDestPath, bsDestFileName, bsDestRangeList;

		CheckCom(mComponent->mVssComponent->GetDirectedTarget(index, &bsSourcePath, &bsSourceFileName, &bsSourceRangeList, &bsDestPath, 
			&bsDestFileName, &bsDestRangeList));
		
		return gcnew VssDirectedTargetInfo(bsSourcePath, bsSourceFileName, bsSourceRangeList, bsDestPath, bsDestFileName, bsDestRangeList);
	}



	//
	// NewTargetList 
	//
	int VssComponent::NewTargetList::Count::get()
	{
		if (mComponent->mVssComponent == 0)
			throw gcnew ObjectDisposedException("Instance of IList used after the object creating it was disposed.");

		UINT count;
		CheckCom(mComponent->mVssComponent->GetNewTargetCount(&count));
		return count;
	}

	
	VssWMFileDescription^ VssComponent::NewTargetList::default::get(int index)
	{
		if (mComponent->mVssComponent == 0)
			throw gcnew ObjectDisposedException("Instance of IList used after the object creating it was disposed.");

		if (index < 0 || index >= Count)
			throw gcnew ArgumentOutOfRangeException("index");

		IVssWMFiledesc *vssWMFiledesc;
		CheckCom(mComponent->mVssComponent->GetNewTarget(index, &vssWMFiledesc));
		return CreateVssWMFileDescription(vssWMFiledesc);
	}

	VssComponent::NewTargetList::NewTargetList(VssComponent^ component)
		: mComponent(component)
	{
	}

	//
	// PartialFileList 
	//
	int VssComponent::PartialFileList::Count::get()
	{
		if (mComponent->mVssComponent == 0)
			throw gcnew ObjectDisposedException("Instance of IList used after the object creating it was disposed.");

		UINT count;
		CheckCom(mComponent->mVssComponent->GetPartialFileCount(&count));
		return count;
	}

	
	VssPartialFileInfo^ VssComponent::PartialFileList::default::get(int index)
	{
		if (mComponent->mVssComponent == 0)
			throw gcnew ObjectDisposedException("Instance of IList used after the object creating it was disposed.");

		if (index < 0 || index >= Count)
			throw gcnew ArgumentOutOfRangeException("index");

		AutoBStr bsPath, bsFileName, bsRange, bsMetadata;
		CheckCom(mComponent->mVssComponent->GetPartialFile(index, &bsPath, &bsFileName, &bsRange, &bsMetadata));
		return gcnew VssPartialFileInfo(bsPath, bsFileName, bsRange, bsMetadata);
	}

	VssComponent::PartialFileList::PartialFileList(VssComponent^ component)
		: mComponent(component)
	{
	}

#if ALPHAVSS_TARGET >= ALPHAVSS_TARGET_WIN2003
	//
	// DifferencedFileList 
	//
	int VssComponent::DifferencedFileList::Count::get()
	{
		if (mComponent->mVssComponent == 0)
			throw gcnew ObjectDisposedException("Instance of IList used after the object creating it was disposed.");

		UINT count;
		CheckCom(mComponent->mVssComponent->GetDifferencedFilesCount(&count));
		return count;
	}

	VssDifferencedFileInfo^ VssComponent::DifferencedFileList::default::get(int index)
	{
		if (mComponent->mVssComponent == 0)
			throw gcnew ObjectDisposedException("Instance of IList used after the object creating it was disposed.");

		if (index < 0 || index >= Count)
			throw gcnew ArgumentOutOfRangeException("index");

		AutoBStr bstrPath, bstrFilespec, bstrLsnString;
		BOOL bRecursive;
		FILETIME ftLastModifyTime;
		CheckCom(mComponent->mVssComponent->GetDifferencedFile(index, &bstrPath, &bstrFilespec, &bRecursive, &bstrLsnString, &ftLastModifyTime));
		return gcnew VssDifferencedFileInfo(bstrPath, bstrFilespec, bRecursive != 0, ToDateTime(ftLastModifyTime));
	}

	VssComponent::DifferencedFileList::DifferencedFileList(VssComponent^ component)
		: mComponent(component)
	{
	}
#endif


	//
	// RestoreSubcomponentList 
	//
	int VssComponent::RestoreSubcomponentList::Count::get()
	{
		if (mComponent->mVssComponent == 0)
			throw gcnew ObjectDisposedException("Instance of IList used after the object creating it was disposed.");

		UINT count;
		CheckCom(mComponent->mVssComponent->GetRestoreSubcomponentCount(&count));
		return count;
	}

	VssRestoreSubcomponentInfo^ VssComponent::RestoreSubcomponentList::default::get(int index)
	{
		if (mComponent->mVssComponent == 0)
			throw gcnew ObjectDisposedException("Instance of IList used after the object creating it was disposed.");

		if (index < 0 || index >= Count)
			throw gcnew ArgumentOutOfRangeException("index");

		AutoBStr bsLogicalPath, bsComponentName;
		bool bRepair;
		CheckCom(mComponent->mVssComponent->GetRestoreSubcomponent(index, &bsLogicalPath, &bsComponentName, &bRepair));
		return gcnew VssRestoreSubcomponentInfo(bsLogicalPath, bsComponentName);
	}

	VssComponent::RestoreSubcomponentList::RestoreSubcomponentList(VssComponent^ component)
		: mComponent(component)
	{
	}


	//
	// AlternateLocationMappingList 
	//
	int VssComponent::AlternateLocationMappingList::Count::get()
	{
		if (mComponent->mVssComponent == 0)
			throw gcnew ObjectDisposedException("Instance of IList used after the object creating it was disposed.");

		UINT count;
		CheckCom(mComponent->mVssComponent->GetAlternateLocationMappingCount(&count));
		return count;
	}

	
	VssWMFileDescription^ VssComponent::AlternateLocationMappingList::default::get(int index)
	{
		if (mComponent->mVssComponent == 0)
			throw gcnew ObjectDisposedException("Instance of IList used after the object creating it was disposed.");

		if (index < 0 || index >= Count)
			throw gcnew ArgumentOutOfRangeException("index");

		IVssWMFiledesc *vssWMFiledesc;
		CheckCom(mComponent->mVssComponent->GetAlternateLocationMapping(index, &vssWMFiledesc));
		return CreateVssWMFileDescription(vssWMFiledesc);
	}

	VssComponent::AlternateLocationMappingList::AlternateLocationMappingList(VssComponent^ component)
		: mComponent(component)
	{
	}

	bool VssComponent::IsAuthoritativeRestore::get()
	{
#ifdef ALPHAVSS_HAS_COMPONENTEX
		bool bAuth;
		if (SUCCEEDED(RequireIVssComponentEx()->GetAuthoritativeRestore(&bAuth)))
			return bAuth;
#endif
		return false;
	}

    String^ VssComponent::PostSnapshotFailureMsg::get()
	{
#ifdef ALPHAVSS_HAS_COMPONENTEX
		AutoBStr bstrMsg;
		if (SUCCEEDED(RequireIVssComponentEx()->GetPostSnapshotFailureMsg(&bstrMsg)))
			return bstrMsg;
#endif
		return nullptr;
	}

    String^ VssComponent::PrepareForBackupFailureMsg::get()
	{
#ifdef ALPHAVSS_HAS_COMPONENTEX
		AutoBStr bstrMsg;
		if (SUCCEEDED(RequireIVssComponentEx()->GetPrepareForBackupFailureMsg(&bstrMsg)))
			return bstrMsg;
#endif
		return nullptr;
	}

    String^ VssComponent::RestoreName::get()
	{
#ifdef ALPHAVSS_HAS_COMPONENTEX
		AutoBStr bstrName;
		if (SUCCEEDED(RequireIVssComponentEx()->GetRestoreName(&bstrName)))
			return bstrName;
#endif
		return nullptr;
	}

	String^ VssComponent::RollForwardRestorePoint::get()
	{
#ifdef ALPHAVSS_HAS_COMPONENTEX
		VSS_ROLLFORWARD_TYPE eRollType;
		AutoBStr bstrPoint;

		if (SUCCEEDED(RequireIVssComponentEx()->GetRollForward(&eRollType, &bstrPoint)))
			return bstrPoint;
#endif
		return nullptr;
	}

	VssRollForwardType VssComponent::RollForwardType::get()
	{
#ifdef ALPHAVSS_HAS_COMPONENTEX
		VSS_ROLLFORWARD_TYPE eRollType;
		AutoBStr bstrPoint;

		if (SUCCEEDED(RequireIVssComponentEx()->GetRollForward(&eRollType, &bstrPoint)))
			return (VssRollForwardType)eRollType;
#endif
		return VssRollForwardType::Undefined;
	}

}
} }
