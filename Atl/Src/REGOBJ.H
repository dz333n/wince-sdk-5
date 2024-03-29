//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//
// RegObj.h : Declaration of the CRegObject

/////////////////////////////////////////////////////////////////////////////
// register

class ATL_NO_VTABLE CDLLRegObject : public CRegObject, public CComObjectRoot,
					  public CComCoClass<CDLLRegObject, &CLSID_Registrar>
{
public:
	CDLLRegObject() {}
	~CDLLRegObject(){CRegObject::ClearReplacements();}

BEGIN_COM_MAP(CDLLRegObject)
	COM_INTERFACE_ENTRY(IRegistrar)
END_COM_MAP()

DECLARE_NOT_AGGREGATABLE(CDLLRegObject)
	HRESULT FinalConstruct()
	{
		return CComObjectRoot::FinalConstruct();
	}
	void FinalRelease()
	{
		CComObjectRoot::FinalRelease();
	}
//we can't use the component because that's what we're registering
//we don't want to do the static registry because we'd have extra code
	static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
	{
		CComObject<CDLLRegObject>* p;
		CComObject<CDLLRegObject>::CreateInstance(&p);
		CComPtr<IRegistrar> pR;
		p->QueryInterface(IID_IRegistrar, (void**)&pR);
		return AtlModuleUpdateRegistryFromResourceD(&_Module,
			(LPCOLESTR)MAKEINTRESOURCE(IDR_Registrar), bRegister, NULL, pR);
	}
};
