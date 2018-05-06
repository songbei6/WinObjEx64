/*******************************************************************************
*
*  (C) COPYRIGHT AUTHORS, 2015 - 2018
*
*  TITLE:       PROPTYPE.C
*
*  VERSION:     1.52
*
*  DATE:        08 Jan 2018
*
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
* TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
*******************************************************************************/
#include "global.h"
#include "propDlg.h"
#include "propTypeConsts.h"

/*
* propSetTypeFlagValue
*
* Purpose:
*
* Add value to the access rights listview
*
*/
VOID propSetTypeFlagValue(
    _In_ HWND	hListView,
    _In_ LPWSTR lpFlag,
    _In_ DWORD	Value
)
{
    INT    nIndex;
    LVITEM lvitem;
    WCHAR  szBuffer[MAX_PATH];

    if (lpFlag == NULL)
        return;

    RtlSecureZeroMemory(&lvitem, sizeof(lvitem));
    lvitem.mask = LVIF_TEXT;
    lvitem.iSubItem = 0;
    lvitem.pszText = lpFlag;
    lvitem.iItem = MAXINT;
    nIndex = ListView_InsertItem(hListView, &lvitem);

    RtlSecureZeroMemory(&szBuffer, sizeof(szBuffer));
    szBuffer[0] = L'0';
    szBuffer[1] = L'x';
    ultohex(Value, &szBuffer[2]);

    lvitem.mask = LVIF_TEXT;
    lvitem.iSubItem = 1;
    lvitem.pszText = szBuffer;
    lvitem.iItem = nIndex;
    ListView_SetItem(hListView, &lvitem);
}

/*
* propSetTypeDecodeValue
*
* Purpose:
*
* Decode Access Right Attributes depending on object type
*
*/
VOID propSetTypeDecodeValue(
    _In_ HWND hListView,
    _In_ DWORD Value,
    _In_ INT TypeIndex
)
{
    INT	        i, Count;
    DWORD       u;
    PVALUE_DESC Desc = NULL;

    switch (TypeIndex) {

    case TYPE_WMIGUID:
        Desc = a_WmiGuidProp;
        Count = MAX_KNOWN_WMIGUID_ATTRIBUTES;
        break;

    case TYPE_WINSTATION:
        Desc = a_WinstaProp;
        Count = MAX_KNOWN_WINSTA_ATTRIBUTES;
        break;

    case TYPE_TOKEN:
        Desc = a_TokenProp;
        Count = MAX_KNOWN_TOKEN_ATTRIBUTES;
        break;

    case TYPE_THREAD:
        Desc = a_ThreadProp;
        Count = MAX_KNOWN_THREAD_ATTRIBUTES;
        break;

    case TYPE_IRTIMER:
    case TYPE_TIMER:
        Desc = a_TimerProp;
        Count = MAX_KNOWN_TIMER_ATTRIBUTES;
        break;

    case TYPE_PROCESS:
        Desc = a_ProcessProp;
        Count = MAX_KNOWN_PROCESS_ATTRIBUTES;
        break;

    case TYPE_KEYEDEVENT:
        Desc = a_KeyedEventProp;
        Count = MAX_KNOWN_KEYEDEVENT_ATTRIBUTES;
        break;

    case TYPE_JOB:
        Desc = a_JobProp;
        Count = MAX_KNOWN_JOB_ATTRIBUTES;
        break;

    case TYPE_DESKTOP:
        Desc = a_DesktopObjectProp;
        Count = MAX_KNOWN_DESKTOP_ATTRIBUTES;
        break;

    case TYPE_DEBUGOBJECT:
        Desc = a_DebugObjectProp;
        Count = MAX_KNOWN_DEBUGOBJECT_ATTRIBUTES;
        break;

    case TYPE_CALLBACK:
        Desc = a_CallbackProp;
        Count = MAX_KNOWN_CALLBACK_ATTRIBUTES;
        break;

    case TYPE_ADAPTER:
    case TYPE_CONTROLLER:
    case TYPE_DEVICE:
    case TYPE_DRIVER:
    case TYPE_FILE:
        Desc = a_FileProp;
        Count = MAX_KNOWN_FILE_ATTRIBUTES;
        break;

    case TYPE_KEY:
        Desc = a_KeyProp;
        Count = MAX_KNOWN_KEY_ATTRIBUTES;
        break;

    case TYPE_TYPE:
        Desc = a_TypeProp;
        Count = MAX_KNOWN_TYPE_ATTRIBUTES;
        break;

    case TYPE_SYMLINK:
        Desc = a_SymLinkProp;
        Count = MAX_KNOWN_SYMLINK_ATTRIBUTES;
        break;

    case TYPE_DIRECTORY:
        Desc = a_DirProp;
        Count = MAX_KNOWN_DIRECTORY_ATTRIBUTES;
        break;

    case TYPE_EVENT:
        Desc = a_EventProp;
        Count = MAX_KNOWN_EVENT_ATTRIBUTES;
        break;

    case TYPE_MUTANT:
        Desc = a_MutantProp;
        Count = MAX_KNOWN_MUTANT_ATTRIBUTES;
        break;

        //all ports
    case TYPE_FLTCOMM_PORT:
    case TYPE_FLTCONN_PORT:
    case TYPE_WAITABLEPORT:
    case TYPE_PORT:
        Desc = a_PortProp;
        Count = MAX_KNOWN_PORT_ATTRIBUTES;
        break;

    case TYPE_PROFILE:
        Desc = a_ProfileProp;
        Count = MAX_KNOWN_PROFILE_ATTRIBUTES;
        break;

    case TYPE_SECTION:
        Desc = a_SectionProp;
        Count = MAX_KNOWN_SECTION_ATTRIBUTES;
        break;

    case TYPE_SEMAPHORE:
        Desc = a_SemaphoreProp;
        Count = MAX_KNOWN_SEMAPHORE_ATTRIBUTES;
        break;

    case TYPE_IOCOMPLETION:
        Desc = a_IoCompletionProp;
        Count = MAX_KNOWN_IOCOMPLETION_ATTRIBUTES;
        break;

        //Transaction Object
    case TYPE_TMTX:
        Desc = a_TmTxProp;
        Count = MAX_KNOWN_TMTX_ATTRIBUTES;
        break;

        //Transaction Resource Manager Object
    case TYPE_TMRM:
        Desc = a_TmRmProp;
        Count = MAX_KNOWN_TMRM_ATTRIBUTES;
        break;

        //Transaction Enlistment Object 
    case TYPE_TMEN:
        Desc = a_TmEnProp;
        Count = MAX_KNOWN_TMEN_ATTRIBUTES;
        break;

        //Transaction Manager Object
    case TYPE_TMTM:
        Desc = a_TmTmProp;
        Count = MAX_KNOWN_TMTM_ATTRIBUTES;
        break;

    case TYPE_TPWORKERFACTORY:
        Desc = a_TpwfProp;
        Count = MAX_KNOWN_TPWORKERFACTORY_ATTRIBUTES;
        break;

    case TYPE_PCWOBJECT:
        Desc = a_PcwProp;
        Count = MAX_KNOWN_PCWOBJECT_ATTRIBUTES;
        break;

    case TYPE_COMPOSITION:
        Desc = a_CompositionProp;
        Count = MAX_KNOWN_COMPOSITION_ATTRIBUTES;
        break;

        //Parition object
    case TYPE_MEMORYPARTITION:
        Desc = a_MemPartProp;
        Count = MAX_KNOWN_MEMPARTITION_ATTRIBUTES;
        break;

    default:
        Count = 0;
        break;
    }

    //list for selected type
    if (Desc) {
        for (i = 0; i < Count; i++) {
            if (Value & Desc[i].dwValue) {
                propSetTypeFlagValue(hListView, Desc[i].lpDescription, Desc[i].dwValue);
                Value &= ~Desc[i].dwValue;
            }
        }
    }

    //list Standard Access Rights if anything left
    if (Value != 0) {
        Desc = a_Standard;
        Count = MAX_KNOWN_STANDARD_ATTRIBUTES;
        for (i = 0; i < Count; i++) {
            if (Value & Desc[i].dwValue) {
                propSetTypeFlagValue(hListView, Desc[i].lpDescription, Desc[i].dwValue);
                Value &= ~Desc[i].dwValue;
            }
        }
    }
    //set unknown to anything else
    if (Value != 0) {
        u = 0x00000001;
        while (Value) {
            if (Value & u) {
                propSetTypeFlagValue(hListView, T_Unknown, u);
                Value &= ~u;
            }
            u *= 2;
            if (u >= MAXIMUM_ALLOWED)
                break;
        }
    }
}

/*
* propSetTypeFlags
*
* Purpose:
*
* Set object type flags descriptions at the Type page
*
*/
VOID propSetTypeFlags(
    HWND hwndDlg,
    DWORD ObjectFlags
)
{
    INT  i;
    HWND hwndCB;
    BOOL bObjectFlagsSet = FALSE;

    hwndCB = GetDlgItem(hwndDlg, IDC_TYPE_FLAGS);
    if (hwndCB) {
        bObjectFlagsSet = (ObjectFlags != 0);
        EnableWindow(hwndCB, bObjectFlagsSet);
        SendMessage(hwndCB, CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
        if (bObjectFlagsSet) {
            EnableWindow(hwndCB, TRUE);
            for (i = 0; i < 8; i++) {
                if (GET_BIT(ObjectFlags, i)) SendMessage(hwndCB, CB_ADDSTRING,
                    (WPARAM)0, (LPARAM)T_ObjectTypeFlags[i]);
            }
            SendMessage(hwndCB, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
        }
    }
}

/*
* propSetTypeAttributes
*
* Purpose:
*
* List attributes depending on object type
*
*/
VOID propSetTypeAttributes(
    _In_ HWND hwndDlg,
    _In_ POBJECT_TYPE_COMPATIBLE ObjectTypeDump
)
{
    LRESULT nIndex;
    HWND    hListAttrbites;
    WCHAR   szBuffer[MAX_PATH + 1];

    if (ObjectTypeDump == NULL)
        return;

    hListAttrbites = GetDlgItem(hwndDlg, ID_TYPE_ATTRLIST);
    if (hListAttrbites == NULL)
        return;

    SendMessage(hListAttrbites, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

    //Invalid attributes
    nIndex = SendMessage(hListAttrbites, LB_ADDSTRING, (WPARAM)0, (LPARAM)&T_InvalidAttributes);
    SendMessage(hListAttrbites, LB_SETITEMDATA, (WPARAM)nIndex,
        (LPARAM)ObjectTypeDump->TypeInfo.InvalidAttributes);
    _strcpy(szBuffer, FORMATTED_ATTRIBUTE);
    ultohex(ObjectTypeDump->TypeInfo.InvalidAttributes, _strend(szBuffer));
    SendMessage(hListAttrbites, LB_ADDSTRING, (WPARAM)0, (LPARAM)&szBuffer);

    //Valid access
    nIndex = SendMessage(hListAttrbites, LB_ADDSTRING, (WPARAM)0, (LPARAM)&T_ValidAccess);
    SendMessage(hListAttrbites, LB_SETITEMDATA, (WPARAM)nIndex,
        (LPARAM)ObjectTypeDump->TypeInfo.ValidAccessMask);
    _strcpy(szBuffer, FORMATTED_ATTRIBUTE);
    ultohex(ObjectTypeDump->TypeInfo.ValidAccessMask, _strend(szBuffer));
    SendMessage(hListAttrbites, LB_ADDSTRING, (WPARAM)0, (LPARAM)&szBuffer);

    //Generic Read
    nIndex = SendMessage(hListAttrbites, LB_ADDSTRING, (WPARAM)0, (LPARAM)&T_GenericRead);
    SendMessage(hListAttrbites, LB_SETITEMDATA, (WPARAM)nIndex,
        (LPARAM)ObjectTypeDump->TypeInfo.GenericMapping.GenericRead);
    _strcpy(szBuffer, FORMATTED_ATTRIBUTE);
    ultohex(ObjectTypeDump->TypeInfo.GenericMapping.GenericRead, _strend(szBuffer));
    SendMessage(hListAttrbites, LB_ADDSTRING, (WPARAM)0, (LPARAM)&szBuffer);

    //Generic Write
    nIndex = SendMessage(hListAttrbites, LB_ADDSTRING, (WPARAM)0, (LPARAM)&T_GenericWrite);
    SendMessage(hListAttrbites, LB_SETITEMDATA, (WPARAM)nIndex,
        (LPARAM)ObjectTypeDump->TypeInfo.GenericMapping.GenericWrite);
    _strcpy(szBuffer, FORMATTED_ATTRIBUTE);
    ultohex(ObjectTypeDump->TypeInfo.GenericMapping.GenericWrite, _strend(szBuffer));
    SendMessage(hListAttrbites, LB_ADDSTRING, (WPARAM)0, (LPARAM)&szBuffer);

    //Generic Execute
    nIndex = SendMessage(hListAttrbites, LB_ADDSTRING, (WPARAM)0, (LPARAM)&T_GenericExecute);
    SendMessage(hListAttrbites, LB_SETITEMDATA, (WPARAM)nIndex,
        (LPARAM)ObjectTypeDump->TypeInfo.GenericMapping.GenericExecute);
    _strcpy(szBuffer, FORMATTED_ATTRIBUTE);
    ultohex(ObjectTypeDump->TypeInfo.GenericMapping.GenericExecute, _strend(szBuffer));
    SendMessage(hListAttrbites, LB_ADDSTRING, (WPARAM)0, (LPARAM)&szBuffer);

    //Generic All
    nIndex = SendMessage(hListAttrbites, LB_ADDSTRING, (WPARAM)0, (LPARAM)&T_GenericAll);
    SendMessage(hListAttrbites, LB_SETITEMDATA, (WPARAM)nIndex,
        (LPARAM)ObjectTypeDump->TypeInfo.GenericMapping.GenericAll);
    _strcpy(szBuffer, FORMATTED_ATTRIBUTE);
    ultohex(ObjectTypeDump->TypeInfo.GenericMapping.GenericAll, _strend(szBuffer));
    SendMessage(hListAttrbites, LB_ADDSTRING, (WPARAM)0, (LPARAM)&szBuffer);
}

/*
* propSetTypeDecodedAttributes
*
* Purpose:
*
* Handler for listbox with access rights and invalid attributes click
*
*/
VOID propSetTypeDecodedAttributes(
    _In_ PROP_OBJECT_INFO *Context,
    _In_ HWND hwndDlg
)
{
    HWND            hListRights, hListAttrbites;
    LRESULT         curSel;
    DWORD           i, dwFlags, a_Count;
    PVALUE_DESC     a_Desc;

    if (Context == NULL) {
        return;
    }

    hListRights = GetDlgItem(hwndDlg, ID_TYPE_ACL_LIST);
    if (hListRights == NULL) {
        return;
    }

    ListView_DeleteAllItems(hListRights);

    hListAttrbites = GetDlgItem(hwndDlg, ID_TYPE_ATTRLIST);
    if (hListAttrbites == NULL) {
        return;
    }

    curSel = SendMessage(hListAttrbites, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
    if (curSel == LB_ERR)
        return;

    if (curSel % 2 != 0) {
        curSel--;
        SendMessage(hListAttrbites, LB_SETCURSEL, (WPARAM)curSel, (LPARAM)0);
    }

    dwFlags = (DWORD)SendMessage(hListAttrbites, LB_GETITEMDATA, (WPARAM)curSel, (LPARAM)0);
    if (dwFlags == 0)
        return;

    //Depending on selection, decode attributes to the list
    if (curSel == 0) {
        //list all known attributes
        a_Count = MAX_KNOWN_OBJECT_ATTRIBUTES;
        a_Desc = a_ObjProp;

        for (i = 0; i < a_Count; i++) {
            if (dwFlags & a_Desc[i].dwValue) {
                propSetTypeFlagValue(hListRights, a_Desc[i].lpDescription, a_Desc[i].dwValue);
                dwFlags &= ~a_Desc[i].dwValue;
            }
        }
        //list any other left
        if (dwFlags != 0) {
            propSetTypeFlagValue(hListRights, T_Unknown, dwFlags);
        }
    }
    else {
        propSetTypeDecodeValue(hListRights, dwFlags, Context->RealTypeIndex);
    }
}

/*
* propSetTypeListView
*
* Purpose:
*
* Create listview for object access rights enumeration.
*
* This routine must be called once.
*
*/
VOID propSetTypeListView(
    _In_ HWND hwndDlg
)
{
    HWND        hListRights;
    LVCOLUMN    col;

    hListRights = GetDlgItem(hwndDlg, ID_TYPE_ACL_LIST);
    if (hListRights == NULL)
        return;

    ListView_SetExtendedListViewStyle(hListRights,
        LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER | LVS_EX_LABELTIP);

    RtlSecureZeroMemory(&col, sizeof(col));
    col.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_FMT | LVCF_WIDTH;
    col.iSubItem = 1;
    col.pszText = TEXT("Flag");
    col.fmt = LVCFMT_LEFT;
    col.iOrder = 0;
    col.cx = 190;
    ListView_InsertColumn(hListRights, col.iSubItem, &col);

    col.iSubItem = 2;
    col.pszText = TEXT("Value");
    col.iOrder = 1;
    col.cx = 80;
    ListView_InsertColumn(hListRights, col.iSubItem, &col);
}

/*
* propQueryTypeInfo
*
* Purpose:
*
* Query Type information depending on object type.
*
* Used if object dumped info not available (restricted user, no driver etc).
*
*/
BOOL propQueryTypeInfo(
    _In_ LPWSTR lpObjectType,
    _Inout_ POBJECT_TYPE_COMPATIBLE pObjectTypeDump
)
{
    BOOL     bResult = FALSE, cond = FALSE;
    ULONG    i;
    SIZE_T   sz;
    LPWSTR   lpType;

    POBJECT_TYPES_INFORMATION pObjectTypes = NULL;
    POBJECT_TYPE_INFORMATION  pObject;

    if (
        (pObjectTypeDump == NULL) ||
        (lpObjectType == NULL)
        )
    {
        return bResult;
    }

    __try {

        do {
            pObjectTypes = supGetObjectTypesInfo();
            if (pObjectTypes == NULL) {
                break;
            }
            pObject = (POBJECT_TYPE_INFORMATION)&pObjectTypes->TypeInformation;
            for (i = 0; i < pObjectTypes->NumberOfTypes; i++) {
                sz = (pObject->TypeName.MaximumLength) + sizeof(UNICODE_NULL);
                lpType = supHeapAlloc(sz);
                if (lpType) {

                    _strncpy(lpType, 
                        sz / sizeof(WCHAR), 
                        pObject->TypeName.Buffer,
                        pObject->TypeName.Length / sizeof(WCHAR));

                    if (_strcmpi(lpType, lpObjectType) == 0) {
                        pObjectTypeDump->TotalNumberOfHandles = pObject->TotalNumberOfHandles;
                        pObjectTypeDump->TotalNumberOfObjects = pObject->TotalNumberOfObjects;
                        pObjectTypeDump->TypeInfo.InvalidAttributes = pObject->InvalidAttributes;
                        pObjectTypeDump->TypeInfo.GenericMapping = pObject->GenericMapping;
                        pObjectTypeDump->TypeInfo.ValidAccessMask = pObject->ValidAccessMask;
                        pObjectTypeDump->TypeInfo.DefaultNonPagedPoolCharge = pObject->DefaultNonPagedPoolCharge;
                        pObjectTypeDump->TypeInfo.DefaultPagedPoolCharge = pObject->DefaultPagedPoolCharge;
                        pObjectTypeDump->HighWaterNumberOfHandles = pObject->HighWaterNumberOfHandles;
                        pObjectTypeDump->HighWaterNumberOfObjects = pObject->HighWaterNumberOfObjects;
                        pObjectTypeDump->TypeInfo.PoolType = pObject->PoolType;
                        if (pObject->SecurityRequired) {
                            SET_BIT(pObjectTypeDump->TypeInfo.ObjectTypeFlags, 3);
                        }
                        if (pObject->MaintainHandleCount) {
                            SET_BIT(pObjectTypeDump->TypeInfo.ObjectTypeFlags, 4);
                        }
                        bResult = TRUE;
                    }
                    supHeapFree(lpType);
                    if (bResult) {
                        break;
                    }
                }
                pObject = (POBJECT_TYPE_INFORMATION)((PCHAR)(pObject + 1) +
                    ALIGN_UP(pObject->TypeName.MaximumLength, sizeof(ULONG_PTR)));
            }
        } while (cond);

        if (pObjectTypes) {
            supHeapFree(pObjectTypes);
        }
    }
    __except (exceptFilter(GetExceptionCode(), GetExceptionInformation())) {
        return FALSE;
    }
    return bResult;
}

/*
* propSetTypeInfo
*
* Purpose:
*
* Set type information depending on object name or type
* Handle special case when user selected \ObjectTypes to provide per type information
*
*/
VOID propSetTypeInfo(
    _In_ PROP_OBJECT_INFO *Context,
    _In_ HWND hwndDlg
)
{
    BOOL                       bOkay;
    INT                        i, nIndex;
    POBJINFO                   pObject = NULL;
    LPCWSTR                    lpTypeDescription = NULL;
    OBJECT_TYPE_COMPATIBLE     ObjectTypeDump;
    WCHAR                      szBuffer[MAX_PATH];
    WCHAR                      szType[MAX_PATH * 2];

    if (Context == NULL) {
        return;
    }

    nIndex = Context->RealTypeIndex;
    if ((Context->RealTypeIndex > TYPE_UNKNOWN) || (Context->RealTypeIndex < TYPE_DEVICE)) {
        nIndex = TYPE_UNKNOWN;
    }

    //if type is not known set it description to it type name
    if (nIndex == TYPE_UNKNOWN) {
        lpTypeDescription = Context->lpObjectType;
    }
    else {
        RtlSecureZeroMemory(&szType, sizeof(szType));
        if (LoadString(g_WinObj.hInstance, TYPE_DESCRIPTION_START_INDEX + nIndex, szType,
            (MAX_PATH * sizeof(WCHAR)) - sizeof(UNICODE_NULL)))
        {
            lpTypeDescription = szType;
        }
        else {
            lpTypeDescription = Context->lpObjectType;
        }
    }

    //check if we have object address and dump object
    if (Context->ObjectInfo.ObjectAddress == 0) {
        propSetTypeFlags(hwndDlg, Context->ObjectFlags);
    }

    //
    // Handle special case 
    // Current object is Object Type, display Type Info
    //
    bOkay = FALSE;
    RtlSecureZeroMemory(&ObjectTypeDump, sizeof(ObjectTypeDump));
    if (Context->IsType) {

        //query object by name, thus were giving us proper object type dump
        pObject = ObQueryObject(T_OBJECTTYPES, Context->lpObjectName);

        //cannot query, no driver or other error, try second method
        if (pObject == NULL) {
            bOkay = propQueryTypeInfo(Context->lpObjectName, &ObjectTypeDump);
        }

        //if type is not known set it description to it type name
        if (Context->RealTypeIndex == TYPE_UNKNOWN)
            lpTypeDescription = Context->lpObjectName;
        else {
            //set description
            RtlSecureZeroMemory(&szType, sizeof(szType));
            if (LoadString(g_WinObj.hInstance, 
                TYPE_DESCRIPTION_START_INDEX + Context->RealTypeIndex, 
                szType,
                (MAX_PATH * 2) - sizeof(UNICODE_NULL)))
            {
                lpTypeDescription = szType;
            }
            else {
                lpTypeDescription = Context->lpObjectType;
            }
        }
    }
    else {
        //
        // Query object type object.
        //
        pObject = ObQueryObject(T_OBJECTTYPES, Context->lpObjectType);

        //
        // If we cannot query because of no driver or other error, try second method.
        //
        if (pObject == NULL) {
            bOkay = propQueryTypeInfo(Context->lpObjectType, &ObjectTypeDump);
        }
    }

    //
    // Set description label.
    //
    SetDlgItemText(hwndDlg, ID_TYPE_DESCRIPTION, lpTypeDescription);

    //
    // Driver info available, dump type.
    //
    if (pObject != NULL) {
        bOkay = ObDumpTypeInfo(pObject->ObjectAddress, &ObjectTypeDump);
        supHeapFree(pObject);
    }

    if (bOkay) {
        //Object count
        RtlSecureZeroMemory(szBuffer, sizeof(szBuffer));
        u64tostr(ObjectTypeDump.TotalNumberOfObjects, _strend(szBuffer));
        SetDlgItemText(hwndDlg, ID_TYPE_COUNT, szBuffer);

        //Handle count
        RtlSecureZeroMemory(szBuffer, sizeof(szBuffer));
        u64tostr(ObjectTypeDump.TotalNumberOfHandles, _strend(szBuffer));
        SetDlgItemText(hwndDlg, ID_TYPE_HANDLECOUNT, szBuffer);

        //Peek object count
        RtlSecureZeroMemory(szBuffer, sizeof(szBuffer));
        u64tostr(ObjectTypeDump.HighWaterNumberOfObjects, _strend(szBuffer));
        SetDlgItemText(hwndDlg, ID_TYPE_PEAKCOUNT, szBuffer);

        //Peek handle count
        RtlSecureZeroMemory(szBuffer, sizeof(szBuffer));
        u64tostr(ObjectTypeDump.HighWaterNumberOfHandles, _strend(szBuffer));
        SetDlgItemText(hwndDlg, ID_TYPE_PEAKHANDLECOUNT, szBuffer);

        //PoolType
        lpTypeDescription = T_Unknown;
        for (i = 0; i < MAX_KNOWN_POOL_TYPES; i++) {
            if (ObjectTypeDump.TypeInfo.PoolType == (POOL_TYPE)a_PoolTypes[i].dwValue) {
                lpTypeDescription = a_PoolTypes[i].lpDescription;
                break;
            }
        }
        SetDlgItemText(hwndDlg, ID_TYPE_POOLTYPE, lpTypeDescription);

        //Default NonPagedPoolCharge
        RtlSecureZeroMemory(szBuffer, sizeof(szBuffer));
        u64tostr(ObjectTypeDump.TypeInfo.DefaultNonPagedPoolCharge, szBuffer);
        SetDlgItemText(hwndDlg, ID_TYPE_NPCHARGE, szBuffer);

        //Default PagedPoolCharge
        RtlSecureZeroMemory(szBuffer, sizeof(szBuffer));
        u64tostr(ObjectTypeDump.TypeInfo.DefaultPagedPoolCharge, _strend(szBuffer));
        SetDlgItemText(hwndDlg, ID_TYPE_PPCHARGE, szBuffer);

        //Type flags
        propSetTypeFlags(hwndDlg, ObjectTypeDump.TypeInfo.ObjectTypeFlags);

        //Access rights
        propSetTypeAttributes(hwndDlg, &ObjectTypeDump);
    }
}

/*
* TypePropDialogProc
*
* Purpose:
*
* Type Properties Dialog Procedure
*
* WM_SHOWWINDOW - when wParam is TRUE it sets "Type" page object information.
* WM_INITDIALOG - initialize object attributes listview, set context window prop.
* WM_DESTROY - remove context window prop.
*
*/
INT_PTR CALLBACK TypePropDialogProc(
    _In_  HWND hwndDlg,
    _In_  UINT uMsg,
    _In_  WPARAM wParam,
    _In_  LPARAM lParam
)
{
    HDC               hDc;
    PAINTSTRUCT       Paint;
    PROPSHEETPAGE    *pSheet = NULL;
    PROP_OBJECT_INFO *Context = NULL;

    switch (uMsg) {
    case WM_SHOWWINDOW:
        Context = GetProp(hwndDlg, T_PROPCONTEXT);
        if (Context) {
            //show window
            if (wParam) {
                propSetTypeInfo(Context, hwndDlg);
                SendDlgItemMessage(hwndDlg, ID_TYPE_ATTRLIST, LB_SETCURSEL,
                    (WPARAM)0, (LPARAM)0);
                SendMessage(hwndDlg, WM_COMMAND,
                    MAKEWPARAM(ID_TYPE_ATTRLIST, LBN_SELCHANGE), 0);
            }
        }
        return 1;
        break;

    case WM_INITDIALOG:
        pSheet = (PROPSHEETPAGE *)lParam;
        if (pSheet) {
            SetProp(hwndDlg, T_PROPCONTEXT, (HANDLE)pSheet->lParam);
        }
        propSetTypeListView(hwndDlg);
        return 1;
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == ID_TYPE_ATTRLIST) {
            if (HIWORD(wParam) == LBN_SELCHANGE) {
                Context = GetProp(hwndDlg, T_PROPCONTEXT);
                propSetTypeDecodedAttributes(Context, hwndDlg);
            }
        }
        return 1;
        break;

    case WM_PAINT:
        Context = GetProp(hwndDlg, T_PROPCONTEXT);
        if (Context) {
            hDc = BeginPaint(hwndDlg, &Paint);
            if (hDc) {
                ImageList_Draw(g_ListViewImages, Context->RealTypeIndex, hDc, 24, 34,
                    ILD_NORMAL | ILD_TRANSPARENT);
                EndPaint(hwndDlg, &Paint);
            }
        }
        return 1;
        break;

    case WM_DESTROY:
        RemoveProp(hwndDlg, T_PROPCONTEXT);
        break;
    }
    return 0;
}
