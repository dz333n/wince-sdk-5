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
//+---------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  File:       sspi.h
//
//  Contents:   Security Support Provider Interface
//              Prototypes and structure definitions
//
//  Functions:  Security Support Provider API
//
//
//----------------------------------------------------------------------------

#ifndef __SSPI_H__
#define __SSPI_H__

#if _MSC_VER > 1000
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif
//
// Microsoft Windows NT version 2.0 and later, wtypes will define HRESULT to be long.
//

typedef WCHAR SEC_WCHAR;
typedef CHAR SEC_CHAR;

typedef LONG SECURITY_STATUS;

#define SEC_TEXT TEXT
#define SEC_FAR
#define SEC_ENTRY WINAPI

#ifdef UNICODE
typedef SEC_WCHAR SEC_FAR * SECURITY_PSTR;
typedef CONST SEC_WCHAR SEC_FAR * SECURITY_PCSTR;
#else // UNICODE
typedef SEC_CHAR SEC_FAR * SECURITY_PSTR;
typedef CONST SEC_CHAR SEC_FAR * SECURITY_PCSTR;
#endif // UNICODE

//
// This is the combined authentication identity structure that may be
// used with the negotiate package, NTLM, Kerberos, or SCHANNEL
//
// (from secext.h)

#ifndef SEC_WINNT_AUTH_IDENTITY_VERSION
#define SEC_WINNT_AUTH_IDENTITY_VERSION 0x200

typedef struct _SEC_WINNT_AUTH_IDENTITY_EXW {
    unsigned long Version;
    unsigned long Length;
    unsigned short SEC_FAR *User;
    unsigned long UserLength;
    unsigned short SEC_FAR *Domain;
    unsigned long DomainLength;
    unsigned short SEC_FAR *Password;
    unsigned long PasswordLength;
    unsigned long Flags;
    unsigned short SEC_FAR * PackageList;
    unsigned long PackageListLength;
} SEC_WINNT_AUTH_IDENTITY_EXW, *PSEC_WINNT_AUTH_IDENTITY_EXW;


typedef struct _SEC_WINNT_AUTH_IDENTITY_EXA {
    unsigned long Version;
    unsigned long Length;
    unsigned char SEC_FAR *User;
    unsigned long UserLength;
    unsigned char SEC_FAR *Domain;
    unsigned long DomainLength;
    unsigned char SEC_FAR *Password;
    unsigned long PasswordLength;
    unsigned long Flags;
    unsigned char SEC_FAR * PackageList;
    unsigned long PackageListLength;
} SEC_WINNT_AUTH_IDENTITY_EXA, *PSEC_WINNT_AUTH_IDENTITY_EXA;

#ifdef UNICODE
#define SEC_WINNT_AUTH_IDENTITY_EX  SEC_WINNT_AUTH_IDENTITY_EXW
#else 
#define SEC_WINNT_AUTH_IDENTITY_EX  SEC_WINNT_AUTH_IDENTITY_EXA
#endif 

#endif // SEC_WINNT_AUTH_IDENTITY_VERSION

//
// Okay, security specific types:
//

#ifndef __SECHANDLE_DEFINED__
typedef struct _SecHandle
{
    ULONG_PTR dwLower ;
    ULONG_PTR dwUpper ;
} SecHandle, * PSecHandle ;

#define __SECHANDLE_DEFINED__
#endif // __SECHANDLE_DEFINED__

#define SecInvalidateHandle( x )    \
            ((PSecHandle) x)->dwLower = (ULONG_PTR) -1 ; \
            ((PSecHandle) x)->dwUpper = (ULONG_PTR) -1 ;

typedef SecHandle CredHandle;
typedef PSecHandle PCredHandle;

typedef SecHandle CtxtHandle;
typedef PSecHandle PCtxtHandle;

typedef LARGE_INTEGER _SECURITY_INTEGER, SECURITY_INTEGER, *PSECURITY_INTEGER;

typedef SECURITY_INTEGER TimeStamp;
typedef PSECURITY_INTEGER PTimeStamp;

//
// If we are in 32 bit mode, define the SECURITY_STRING structure,
// as a clone of the base UNICODE_STRING structure.  This is used
// internally in security components, an as the string interface
// for kernel components (e.g. FSPs)
//

typedef struct _SECURITY_STRING {
    unsigned short      Length;
    unsigned short      MaximumLength;
    unsigned short *    Buffer;
} SECURITY_STRING, * PSECURITY_STRING;

//
// SecPkgInfo structure
//
//  Provides general information about a security provider
//

typedef struct _SecPkgInfoW
{
    unsigned long fCapabilities;        // Capability bitmask
    unsigned short wVersion;            // Version of driver
    unsigned short wRPCID;              // ID for RPC Runtime
    unsigned long cbMaxToken;           // Size of authentication token (max)
    SEC_WCHAR SEC_FAR * Name;           // Text name
    SEC_WCHAR SEC_FAR * Comment;        // Comment
} SecPkgInfoW, SEC_FAR * PSecPkgInfoW;

typedef struct _SecPkgInfoA
{
    unsigned long fCapabilities;        // Capability bitmask
    unsigned short wVersion;            // Version of driver
    unsigned short wRPCID;              // ID for RPC Runtime
    unsigned long cbMaxToken;           // Size of authentication token (max)
    SEC_CHAR SEC_FAR * Name;            // Text name
    SEC_CHAR SEC_FAR * Comment;         // Comment
} SecPkgInfoA, SEC_FAR * PSecPkgInfoA;

#ifdef UNICODE
#define SecPkgInfo SecPkgInfoW
#define PSecPkgInfo PSecPkgInfoW
#else
#define SecPkgInfo SecPkgInfoA
#define PSecPkgInfo PSecPkgInfoA
#endif // !UNICODE

//
//  Security Package Capabilities
//
#define SECPKG_FLAG_INTEGRITY       0x00000001  // Supports integrity on messages
#define SECPKG_FLAG_PRIVACY         0x00000002  // Supports privacy (confidentiality)
#define SECPKG_FLAG_TOKEN_ONLY      0x00000004  // Only security token needed
#define SECPKG_FLAG_DATAGRAM        0x00000008  // Datagram RPC support
#define SECPKG_FLAG_CONNECTION      0x00000010  // Connection oriented RPC support
#define SECPKG_FLAG_MULTI_REQUIRED  0x00000020  // Full 3-leg required for re-auth.
#define SECPKG_FLAG_CLIENT_ONLY     0x00000040  // Server side functionality not available
#define SECPKG_FLAG_EXTENDED_ERROR  0x00000080  // Supports extended error msgs
#define SECPKG_FLAG_IMPERSONATION   0x00000100  // Supports impersonation
#define SECPKG_FLAG_ACCEPT_WIN32_NAME   0x00000200  // Accepts Win32 names
#define SECPKG_FLAG_STREAM          0x00000400  // Supports stream semantics
#define SECPKG_FLAG_NEGOTIABLE      0x00000800  // Can be used by the negotiate package
#define SECPKG_FLAG_GSS_COMPATIBLE  0x00001000  // GSS Compatibility Available
#define SECPKG_FLAG_LOGON           0x00002000  // Supports common LsaLogonUser
#define SECPKG_FLAG_ASCII_BUFFERS   0x00004000  // Token Buffers are in ASCII
#define SECPKG_FLAG_FRAGMENT        0x00008000  // Package can fragment to fit
#define SECPKG_FLAG_MUTUAL_AUTH     0x00010000  // Package can perform mutual authentication
#define SECPKG_FLAG_DELEGATION      0x00020000  // Package can delegate

#define SECPKG_ID_NONE      0xFFFF

//
// SecBuffer
//
//  Generic memory descriptors for buffers passed in to the security
//  API
//

typedef struct _SecBuffer {
    unsigned long cbBuffer;             // Size of the buffer, in bytes
    unsigned long BufferType;           // Type of the buffer (below)
    void SEC_FAR * pvBuffer;            // Pointer to the buffer
} SecBuffer, SEC_FAR * PSecBuffer;

typedef struct _SecBufferDesc {
    unsigned long ulVersion;            // Version number
    unsigned long cBuffers;             // Number of buffers
    PSecBuffer pBuffers;                // Pointer to array of buffers
} SecBufferDesc, SEC_FAR * PSecBufferDesc;

#define SECBUFFER_VERSION           0

#define SECBUFFER_EMPTY             0   // Undefined, replaced by provider
#define SECBUFFER_DATA              1   // Packet data
#define SECBUFFER_TOKEN             2   // Security token
#define SECBUFFER_PKG_PARAMS        3   // Package specific parameters
#define SECBUFFER_MISSING           4   // Missing Data indicator
#define SECBUFFER_EXTRA             5   // Extra data
#define SECBUFFER_STREAM_TRAILER    6   // Security Trailer
#define SECBUFFER_STREAM_HEADER     7   // Security Header
#define SECBUFFER_NEGOTIATION_INFO  8   // Hints from the negotiation pkg
#define SECBUFFER_PADDING           9   // non-data padding
#define SECBUFFER_STREAM            10  // whole encrypted message

#define SECBUFFER_ATTRMASK          0xF0000000
#define SECBUFFER_READONLY          0x80000000  // Buffer is read-only
#define SECBUFFER_RESERVED          0x40000000

typedef struct _SEC_NEGOTIATION_INFO {
    unsigned long       Size;           // Size of this structure
    unsigned long       NameLength;     // Length of name hint
    SEC_WCHAR SEC_FAR * Name;           // Name hint
    void SEC_FAR *      Reserved;       // Reserved
} SEC_NEGOTIATION_INFO, SEC_FAR * PSEC_NEGOTIATION_INFO ;

//
//  Data Representation Constant:
//
#define SECURITY_NATIVE_DREP        0x00000010
#define SECURITY_NETWORK_DREP       0x00000000

//
//  Credential Use Flags
//
#define SECPKG_CRED_INBOUND         0x00000001
#define SECPKG_CRED_OUTBOUND        0x00000002
#define SECPKG_CRED_BOTH            0x00000003
#define SECPKG_CRED_DEFAULT         0x00000004
#define SECPKG_CRED_RESERVED        0xF0000000

//
//  InitializeSecurityContext Requirement and return flags:
//

#define ISC_REQ_DELEGATE                0x00000001
#define ISC_REQ_MUTUAL_AUTH             0x00000002
#define ISC_REQ_REPLAY_DETECT           0x00000004
#define ISC_REQ_SEQUENCE_DETECT         0x00000008
#define ISC_REQ_CONFIDENTIALITY         0x00000010
#define ISC_REQ_USE_SESSION_KEY         0x00000020
#define ISC_REQ_PROMPT_FOR_CREDS        0x00000040
#define ISC_REQ_USE_SUPPLIED_CREDS      0x00000080
#define ISC_REQ_ALLOCATE_MEMORY         0x00000100
#define ISC_REQ_USE_DCE_STYLE           0x00000200
#define ISC_REQ_DATAGRAM                0x00000400
#define ISC_REQ_CONNECTION              0x00000800
#define ISC_REQ_CALL_LEVEL              0x00001000
#define ISC_REQ_FRAGMENT_SUPPLIED       0x00002000
#define ISC_REQ_EXTENDED_ERROR          0x00004000
#define ISC_REQ_STREAM                  0x00008000
#define ISC_REQ_INTEGRITY               0x00010000
#define ISC_REQ_IDENTIFY                0x00020000
#define ISC_REQ_NULL_SESSION            0x00040000
#define ISC_REQ_MANUAL_CRED_VALIDATION  0x00080000
#define ISC_REQ_RESERVED1               0x00100000
#define ISC_REQ_FRAGMENT_TO_FIT         0x00200000

#define ISC_RET_DELEGATE                0x00000001
#define ISC_RET_MUTUAL_AUTH             0x00000002
#define ISC_RET_REPLAY_DETECT           0x00000004
#define ISC_RET_SEQUENCE_DETECT         0x00000008
#define ISC_RET_CONFIDENTIALITY         0x00000010
#define ISC_RET_USE_SESSION_KEY         0x00000020
#define ISC_RET_USED_COLLECTED_CREDS    0x00000040
#define ISC_RET_USED_SUPPLIED_CREDS     0x00000080
#define ISC_RET_ALLOCATED_MEMORY        0x00000100
#define ISC_RET_USED_DCE_STYLE          0x00000200
#define ISC_RET_DATAGRAM                0x00000400
#define ISC_RET_CONNECTION              0x00000800
#define ISC_RET_INTERMEDIATE_RETURN     0x00001000
#define ISC_RET_CALL_LEVEL              0x00002000
#define ISC_RET_EXTENDED_ERROR          0x00004000
#define ISC_RET_STREAM                  0x00008000
#define ISC_RET_INTEGRITY               0x00010000
#define ISC_RET_IDENTIFY                0x00020000
#define ISC_RET_NULL_SESSION            0x00040000
#define ISC_RET_MANUAL_CRED_VALIDATION  0x00080000
#define ISC_RET_RESERVED1               0x00100000
#define ISC_RET_FRAGMENT_ONLY           0x00200000

#define ASC_REQ_DELEGATE                0x00000001
#define ASC_REQ_MUTUAL_AUTH             0x00000002
#define ASC_REQ_REPLAY_DETECT           0x00000004
#define ASC_REQ_SEQUENCE_DETECT         0x00000008
#define ASC_REQ_CONFIDENTIALITY         0x00000010
#define ASC_REQ_USE_SESSION_KEY         0x00000020
#define ASC_REQ_ALLOCATE_MEMORY         0x00000100
#define ASC_REQ_USE_DCE_STYLE           0x00000200
#define ASC_REQ_DATAGRAM                0x00000400
#define ASC_REQ_CONNECTION              0x00000800
#define ASC_REQ_CALL_LEVEL              0x00001000
#define ASC_REQ_EXTENDED_ERROR          0x00008000
#define ASC_REQ_STREAM                  0x00010000
#define ASC_REQ_INTEGRITY               0x00020000
#define ASC_REQ_LICENSING               0x00040000
#define ASC_REQ_IDENTIFY                0x00080000
#define ASC_REQ_ALLOW_NULL_SESSION      0x00100000
#define ASC_REQ_ALLOW_NON_USER_LOGONS   0x00200000
#define ASC_REQ_ALLOW_CONTEXT_REPLAY    0x00400000
#define ASC_REQ_FRAGMENT_TO_FIT         0x00800000
#define ASC_REQ_FRAGMENT_SUPPLIED       0x00002000

#define ASC_RET_DELEGATE                0x00000001
#define ASC_RET_MUTUAL_AUTH             0x00000002
#define ASC_RET_REPLAY_DETECT           0x00000004
#define ASC_RET_SEQUENCE_DETECT         0x00000008
#define ASC_RET_CONFIDENTIALITY         0x00000010
#define ASC_RET_USE_SESSION_KEY         0x00000020
#define ASC_RET_ALLOCATED_MEMORY        0x00000100
#define ASC_RET_USED_DCE_STYLE          0x00000200
#define ASC_RET_DATAGRAM                0x00000400
#define ASC_RET_CONNECTION              0x00000800
#define ASC_RET_CALL_LEVEL              0x00002000 // skipped 1000 to be like ISC_
#define ASC_RET_THIRD_LEG_FAILED        0x00004000
#define ASC_RET_EXTENDED_ERROR          0x00008000
#define ASC_RET_STREAM                  0x00010000
#define ASC_RET_INTEGRITY               0x00020000
#define ASC_RET_LICENSING               0x00040000
#define ASC_RET_IDENTIFY                0x00080000
#define ASC_RET_NULL_SESSION            0x00100000
#define ASC_RET_ALLOW_NON_USER_LOGONS   0x00200000
#define ASC_RET_ALLOW_CONTEXT_REPLAY    0x00400000
#define ASC_RET_FRAGMENT_ONLY           0x00800000

//
//  Security Credentials Attributes:
//

#define SECPKG_CRED_ATTR_NAMES 1

typedef struct _SecPkgCredentials_NamesW
{
    SEC_WCHAR SEC_FAR * sUserName;
} SecPkgCredentials_NamesW, SEC_FAR * PSecPkgCredentials_NamesW;

typedef struct _SecPkgCredentials_NamesA
{
    SEC_CHAR SEC_FAR * sUserName;
} SecPkgCredentials_NamesA, SEC_FAR * PSecPkgCredentials_NamesA;

#ifdef UNICODE
#define SecPkgCredentials_Names SecPkgCredentials_NamesW
#define PSecPkgCredentials_Names PSecPkgCredentials_NamesW
#else
#define SecPkgCredentials_Names SecPkgCredentials_NamesA
#define PSecPkgCredentials_Names PSecPkgCredentials_NamesA
#endif // !UNICODE

//
//  Security Context Attributes:
//

#define SECPKG_ATTR_SIZES           0
#define SECPKG_ATTR_NAMES           1
#define SECPKG_ATTR_LIFESPAN        2
#define SECPKG_ATTR_DCE_INFO        3
#define SECPKG_ATTR_STREAM_SIZES    4
#define SECPKG_ATTR_KEY_INFO        5
#define SECPKG_ATTR_AUTHORITY       6
#define SECPKG_ATTR_PROTO_INFO      7
#define SECPKG_ATTR_PASSWORD_EXPIRY 8
#define SECPKG_ATTR_SESSION_KEY     9
#define SECPKG_ATTR_PACKAGE_INFO    10
#define SECPKG_ATTR_USER_FLAGS      11
#define SECPKG_ATTR_NEGOTIATION_INFO 12
#define SECPKG_ATTR_NATIVE_NAMES    13
#define SECPKG_ATTR_FLAGS           14


typedef struct _SecPkgContext_Sizes
{
    unsigned long cbMaxToken;
    unsigned long cbMaxSignature;
    unsigned long cbBlockSize;
    unsigned long cbSecurityTrailer;
} SecPkgContext_Sizes, SEC_FAR * PSecPkgContext_Sizes;

typedef struct _SecPkgContext_StreamSizes
{
    unsigned long   cbHeader;
    unsigned long   cbTrailer;
    unsigned long   cbMaximumMessage;
    unsigned long   cBuffers;
    unsigned long   cbBlockSize;
} SecPkgContext_StreamSizes, * PSecPkgContext_StreamSizes;

typedef struct _SecPkgContext_NamesW
{
    SEC_WCHAR SEC_FAR * sUserName;
} SecPkgContext_NamesW, SEC_FAR * PSecPkgContext_NamesW;

typedef struct _SecPkgContext_NamesA
{
    SEC_CHAR SEC_FAR * sUserName;
} SecPkgContext_NamesA, SEC_FAR * PSecPkgContext_NamesA;

#ifdef UNICODE
#define SecPkgContext_Names SecPkgContext_NamesW
#define PSecPkgContext_Names PSecPkgContext_NamesW
#else
#define SecPkgContext_Names SecPkgContext_NamesA
#define PSecPkgContext_Names PSecPkgContext_NamesA
#endif // !UNICODE

typedef struct _SecPkgContext_Lifespan
{
    TimeStamp tsStart;
    TimeStamp tsExpiry;
} SecPkgContext_Lifespan, SEC_FAR * PSecPkgContext_Lifespan;

typedef struct _SecPkgContext_DceInfo
{
    unsigned long AuthzSvc;
    void SEC_FAR * pPac;
} SecPkgContext_DceInfo, SEC_FAR * PSecPkgContext_DceInfo;

typedef struct _SecPkgContext_KeyInfoA
{
    SEC_CHAR SEC_FAR *  sSignatureAlgorithmName;
    SEC_CHAR SEC_FAR *  sEncryptAlgorithmName;
    unsigned long       KeySize;
    unsigned long       SignatureAlgorithm;
    unsigned long       EncryptAlgorithm;
} SecPkgContext_KeyInfoA, SEC_FAR * PSecPkgContext_KeyInfoA;

typedef struct _SecPkgContext_KeyInfoW
{
    SEC_WCHAR SEC_FAR * sSignatureAlgorithmName;
    SEC_WCHAR SEC_FAR * sEncryptAlgorithmName;
    unsigned long       KeySize;
    unsigned long       SignatureAlgorithm;
    unsigned long       EncryptAlgorithm;
} SecPkgContext_KeyInfoW, SEC_FAR * PSecPkgContext_KeyInfoW;

#ifdef UNICODE
#define SecPkgContext_KeyInfo SecPkgContext_KeyInfoW
#define PSecPkgContext_KeyInfo PSecPkgContext_KeyInfoW
#else
#define SecPkgContext_KeyInfo SecPkgContext_KeyInfoA
#define PSecPkgContext_KeyInfo PSecPkgContext_KeyInfoA
#endif

typedef struct _SecPkgContext_AuthorityA
{
    SEC_CHAR SEC_FAR * sAuthorityName;
} SecPkgContext_AuthorityA, * PSecPkgContext_AuthorityA;

typedef struct _SecPkgContext_AuthorityW
{
    SEC_WCHAR SEC_FAR * sAuthorityName;
} SecPkgContext_AuthorityW, * PSecPkgContext_AuthorityW;

#ifdef UNICODE
#define SecPkgContext_Authority SecPkgContext_AuthorityW
#define PSecPkgContext_Authority PSecPkgContext_AuthorityW
#else
#define SecPkgContext_Authority SecPkgContext_AuthorityA
#define PSecPkgContext_Authority PSecPkgContext_AuthorityA
#endif

typedef struct _SecPkgContext_ProtoInfoA
{
    SEC_CHAR SEC_FAR *  sProtocolName;
    unsigned long       majorVersion;
    unsigned long       minorVersion;
} SecPkgContext_ProtoInfoA, SEC_FAR * PSecPkgContext_ProtoInfoA;

typedef struct _SecPkgContext_ProtoInfoW
{
    SEC_WCHAR SEC_FAR * sProtocolName;
    unsigned long       majorVersion;
    unsigned long       minorVersion;
} SecPkgContext_ProtoInfoW, SEC_FAR * PSecPkgContext_ProtoInfoW;

#ifdef UNICODE
#define SecPkgContext_ProtoInfo SecPkgContext_ProtoInfoW
#define PSecPkgContext_ProtoInfo PSecPkgContext_ProtoInfoW
#else
#define SecPkgContext_ProtoInfo SecPkgContext_ProtoInfoA
#define PSecPkgContext_ProtoInfo PSecPkgContext_ProtoInfoA
#endif

typedef struct _SecPkgContext_PasswordExpiry
{
    TimeStamp tsPasswordExpires;
} SecPkgContext_PasswordExpiry, SEC_FAR * PSecPkgContext_PasswordExpiry;

typedef struct _SecPkgContext_SessionKey
{
    unsigned long SessionKeyLength;
    unsigned char SEC_FAR * SessionKey;
} SecPkgContext_SessionKey, * PSecPkgContext_SessionKey;

typedef struct _SecPkgContext_PackageInfoW
{
    PSecPkgInfoW PackageInfo;
} SecPkgContext_PackageInfoW, SEC_FAR * PSecPkgContext_PackageInfoW;


typedef struct _SecPkgContext_PackageInfoA
{
    PSecPkgInfoA PackageInfo;
} SecPkgContext_PackageInfoA, SEC_FAR * PSecPkgContext_PackageInfoA;

typedef struct _SecPkgContext_UserFlags
{
    unsigned long UserFlags;
} SecPkgContext_UserFlags, SEC_FAR * PSecPkgContext_UserFlags;

typedef struct _SecPkgContext_Flags
{
    unsigned long Flags;
} SecPkgContext_Flags, SEC_FAR * PSecPkgContext_Flags;

#ifdef UNICODE
#define SecPkgContext_PackageInfo   SecPkgContext_PackageInfoW      // ntifs
#define PSecPkgContext_PackageInfo  PSecPkgContext_PackageInfoW     // ntifs
#else
#define SecPkgContext_PackageInfo   SecPkgContext_PackageInfoA
#define PSecPkgContext_PackageInfo  PSecPkgContext_PackageInfoA
#endif

typedef struct _SecPkgContext_NegotiationInfoA
{
    PSecPkgInfoA    PackageInfo ;
    unsigned long   NegotiationState ;
} SecPkgContext_NegotiationInfoA, SEC_FAR * PSecPkgContext_NegotiationInfoA ;

typedef struct _SecPkgContext_NegotiationInfoW
{
    PSecPkgInfoW    PackageInfo ;
    unsigned long   NegotiationState ;
} SecPkgContext_NegotiationInfoW, SEC_FAR * PSecPkgContext_NegotiationInfoW ;

#ifdef UNICODE
#define SecPkgContext_NegotiationInfo   SecPkgContext_NegotiationInfoW
#define PSecPkgContext_NegotiationInfo  PSecPkgContext_NegotiationInfoW
#else
#define SecPkgContext_NegotiationInfo   SecPkgContext_NegotiationInfoA
#define PSecPkgContext_NegotiationInfo  PSecPkgContext_NegotiationInfoA
#endif

#define SECPKG_NEGOTIATION_COMPLETE     0
#define SECPKG_NEGOTIATION_OPTIMISTIC   1
#define SECPKG_NEGOTIATION_IN_PROGRESS  2
#define SECPKG_NEGOTIATION_DIRECT       3


typedef struct _SecPkgContext_NativeNamesW
{
    SEC_WCHAR SEC_FAR * sClientName;
    SEC_WCHAR SEC_FAR * sServerName;
} SecPkgContext_NativeNamesW, SEC_FAR * PSecPkgContext_NativeNamesW;

typedef struct _SecPkgContext_NativeNamesA
{
    SEC_CHAR SEC_FAR * sClientName;
    SEC_CHAR SEC_FAR * sServerName;
} SecPkgContext_NativeNamesA, SEC_FAR * PSecPkgContext_NativeNamesA;


#ifdef UNICODE
#  define SecPkgContext_NativeNames SecPkgContext_NativeNamesW          // ntifs
#  define PSecPkgContext_NativeNames PSecPkgContext_NativeNamesW        // ntifs
#else
#  define SecPkgContext_NativeNames SecPkgContext_NativeNamesA
#  define PSecPkgContext_NativeNames PSecPkgContext_NativeNamesA
#endif // !UNICODE


#ifndef SECPKG_ATTR_GROUP_NAMES
// Microsoft Windows CE only
#define SECPKG_ATTR_GROUP_NAMES     30
typedef struct _SecPkgContext_GroupNamesW
{
    SEC_WCHAR SEC_FAR * msGroupNames;  // multi-string list of groups
} SecPkgContext_GroupNamesW, SEC_FAR * PSecPkgContext_GroupNamesW;

#ifdef UNICODE
#define SecPkgContext_GroupNames SecPkgContext_GroupNamesW
#define PSecPkgContext_GroupNames PSecPkgContext_GroupNamesW
#endif
#endif

typedef void
(SEC_ENTRY SEC_FAR * SEC_GET_KEY_FN) (
    void SEC_FAR * Arg,                 // Argument passed in
    void SEC_FAR * Principal,           // Principal ID
    unsigned long KeyVer,               // Key Version
    void SEC_FAR * SEC_FAR * Key,       // Returned ptr to key
    SECURITY_STATUS SEC_FAR * Status    // returned status
    );


SECURITY_STATUS SEC_ENTRY
AcquireCredentialsHandleW(
    SEC_WCHAR SEC_FAR * pszPrincipal,   // Name of principal
    SEC_WCHAR SEC_FAR * pszPackage,     // Name of package
    unsigned long fCredentialUse,       // Flags indicating use
    void SEC_FAR * pvLogonId,           // Pointer to logon ID
    void SEC_FAR * pAuthData,           // Package specific data
    SEC_GET_KEY_FN pGetKeyFn,           // Pointer to GetKey() func
    void SEC_FAR * pvGetKeyArgument,    // Value to pass to GetKey()
    PCredHandle phCredential,           // (out) Cred Handle
    PTimeStamp ptsExpiry                // (out) Lifetime (optional)
    );

typedef SECURITY_STATUS
(SEC_ENTRY * ACQUIRE_CREDENTIALS_HANDLE_FN_W)(
    SEC_WCHAR SEC_FAR *,
    SEC_WCHAR SEC_FAR *,
    unsigned long,
    void SEC_FAR *,
    void SEC_FAR *,
    SEC_GET_KEY_FN,
    void SEC_FAR *,
    PCredHandle,
    PTimeStamp);

SECURITY_STATUS SEC_ENTRY
AcquireCredentialsHandleA(
    SEC_CHAR SEC_FAR * pszPrincipal,    // Name of principal
    SEC_CHAR SEC_FAR * pszPackage,      // Name of package
    unsigned long fCredentialUse,       // Flags indicating use
    void SEC_FAR * pvLogonId,           // Pointer to logon ID
    void SEC_FAR * pAuthData,           // Package specific data
    SEC_GET_KEY_FN pGetKeyFn,           // Pointer to GetKey() func
    void SEC_FAR * pvGetKeyArgument,    // Value to pass to GetKey()
    PCredHandle phCredential,           // (out) Cred Handle
    PTimeStamp ptsExpiry                // (out) Lifetime (optional)
    );

typedef SECURITY_STATUS
(SEC_ENTRY * ACQUIRE_CREDENTIALS_HANDLE_FN_A)(
    SEC_CHAR SEC_FAR *,
    SEC_CHAR SEC_FAR *,
    unsigned long,
    void SEC_FAR *,
    void SEC_FAR *,
    SEC_GET_KEY_FN,
    void SEC_FAR *,
    PCredHandle,
    PTimeStamp);

#ifdef UNICODE
#define AcquireCredentialsHandle AcquireCredentialsHandleW
#define ACQUIRE_CREDENTIALS_HANDLE_FN ACQUIRE_CREDENTIALS_HANDLE_FN_W
#else
#define AcquireCredentialsHandle AcquireCredentialsHandleA
#define ACQUIRE_CREDENTIALS_HANDLE_FN ACQUIRE_CREDENTIALS_HANDLE_FN_A
#endif // !UNICODE

SECURITY_STATUS SEC_ENTRY
FreeCredentialsHandle(
    PCredHandle phCredential            // Handle to free
    );

typedef SECURITY_STATUS
(SEC_ENTRY * FREE_CREDENTIALS_HANDLE_FN)(
    PCredHandle );


////////////////////////////////////////////////////////////////////////
///
/// Context Management Functions
///
////////////////////////////////////////////////////////////////////////

SECURITY_STATUS SEC_ENTRY
InitializeSecurityContextW(
    PCredHandle phCredential,               // Cred to base context
    PCtxtHandle phContext,                  // Existing context (OPT)
    SEC_WCHAR SEC_FAR * pszTargetName,      // Name of target
    unsigned long fContextReq,              // Context Requirements
    unsigned long Reserved1,                // Reserved, MBZ
    unsigned long TargetDataRep,            // Data rep of target
    PSecBufferDesc pInput,                  // Input Buffers
    unsigned long Reserved2,                // Reserved, MBZ
    PCtxtHandle phNewContext,               // (out) New Context handle
    PSecBufferDesc pOutput,                 // (inout) Output Buffers
    unsigned long SEC_FAR * pfContextAttr,  // (out) Context attrs
    PTimeStamp ptsExpiry                    // (out) Life span (OPT)
    );

typedef SECURITY_STATUS
(SEC_ENTRY * INITIALIZE_SECURITY_CONTEXT_FN_W)(
    PCredHandle,
    PCtxtHandle,
    SEC_WCHAR SEC_FAR *,
    unsigned long,
    unsigned long,
    unsigned long,
    PSecBufferDesc,
    unsigned long,
    PCtxtHandle,
    PSecBufferDesc,
    unsigned long SEC_FAR *,
    PTimeStamp);

SECURITY_STATUS SEC_ENTRY
InitializeSecurityContextA(
    PCredHandle phCredential,               // Cred to base context
    PCtxtHandle phContext,                  // Existing context (OPT)
    SEC_CHAR SEC_FAR * pszTargetName,       // Name of target
    unsigned long fContextReq,              // Context Requirements
    unsigned long Reserved1,                // Reserved, MBZ
    unsigned long TargetDataRep,            // Data rep of target
    PSecBufferDesc pInput,                  // Input Buffers
    unsigned long Reserved2,                // Reserved, MBZ
    PCtxtHandle phNewContext,               // (out) New Context handle
    PSecBufferDesc pOutput,                 // (inout) Output Buffers
    unsigned long SEC_FAR * pfContextAttr,  // (out) Context attrs
    PTimeStamp ptsExpiry                    // (out) Life span (OPT)
    );

typedef SECURITY_STATUS
(SEC_ENTRY * INITIALIZE_SECURITY_CONTEXT_FN_A)(
    PCredHandle,
    PCtxtHandle,
    SEC_CHAR SEC_FAR *,
    unsigned long,
    unsigned long,
    unsigned long,
    PSecBufferDesc,
    unsigned long,
    PCtxtHandle,
    PSecBufferDesc,
    unsigned long SEC_FAR *,
    PTimeStamp);

#ifdef UNICODE
#define InitializeSecurityContext InitializeSecurityContextW
#define INITIALIZE_SECURITY_CONTEXT_FN INITIALIZE_SECURITY_CONTEXT_FN_W
#else
#define InitializeSecurityContext InitializeSecurityContextA
#define INITIALIZE_SECURITY_CONTEXT_FN INITIALIZE_SECURITY_CONTEXT_FN_A
#endif // !UNICODE

SECURITY_STATUS SEC_ENTRY
AcceptSecurityContext(
    PCredHandle phCredential,               // Cred to base context
    PCtxtHandle phContext,                  // Existing context (OPT)
    PSecBufferDesc pInput,                  // Input buffer
    unsigned long fContextReq,              // Context Requirements
    unsigned long TargetDataRep,            // Target Data Rep
    PCtxtHandle phNewContext,               // (out) New context handle
    PSecBufferDesc pOutput,                 // (inout) Output buffers
    unsigned long SEC_FAR * pfContextAttr,  // (out) Context attributes
    PTimeStamp ptsExpiry                    // (out) Life span (OPT)
    );

typedef SECURITY_STATUS
(SEC_ENTRY * ACCEPT_SECURITY_CONTEXT_FN)(
    PCredHandle,
    PCtxtHandle,
    PSecBufferDesc,
    unsigned long,
    unsigned long,
    PCtxtHandle,
    PSecBufferDesc,
    unsigned long SEC_FAR *,
    PTimeStamp);

SECURITY_STATUS SEC_ENTRY
CompleteAuthToken(
    PCtxtHandle phContext,              // Context to complete
    PSecBufferDesc pToken               // Token to complete
    );

typedef SECURITY_STATUS
(SEC_ENTRY * COMPLETE_AUTH_TOKEN_FN)(
    PCtxtHandle,
    PSecBufferDesc);

SECURITY_STATUS SEC_ENTRY
ImpersonateSecurityContext(
    PCtxtHandle phContext               // Context to impersonate
    );

typedef SECURITY_STATUS
(SEC_ENTRY * IMPERSONATE_SECURITY_CONTEXT_FN)(
    PCtxtHandle);

SECURITY_STATUS SEC_ENTRY
RevertSecurityContext(
    PCtxtHandle phContext               // Context from which to re
    );

typedef SECURITY_STATUS
(SEC_ENTRY * REVERT_SECURITY_CONTEXT_FN)(
    PCtxtHandle);

SECURITY_STATUS SEC_ENTRY
QuerySecurityContextToken(
    PCtxtHandle phContext,
    void SEC_FAR * SEC_FAR * Token
    );

typedef SECURITY_STATUS
(SEC_ENTRY * QUERY_SECURITY_CONTEXT_TOKEN_FN)(
    PCtxtHandle, void SEC_FAR * SEC_FAR *);

SECURITY_STATUS SEC_ENTRY
DeleteSecurityContext(
    PCtxtHandle phContext               // Context to delete
    );

typedef SECURITY_STATUS
(SEC_ENTRY * DELETE_SECURITY_CONTEXT_FN)(
    PCtxtHandle);

SECURITY_STATUS SEC_ENTRY
ApplyControlToken(
    PCtxtHandle phContext,              // Context to modify
    PSecBufferDesc pInput               // Input token to apply
    );

typedef SECURITY_STATUS
(SEC_ENTRY * APPLY_CONTROL_TOKEN_FN)(
    PCtxtHandle, PSecBufferDesc);

SECURITY_STATUS SEC_ENTRY
QueryContextAttributesW(
    PCtxtHandle phContext,              // Context to query
    unsigned long ulAttribute,          // Attribute to query
    void SEC_FAR * pBuffer              // Buffer for attributes
    );

typedef SECURITY_STATUS
(SEC_ENTRY * QUERY_CONTEXT_ATTRIBUTES_FN_W)(
    PCtxtHandle,
    unsigned long,
    void SEC_FAR *);

SECURITY_STATUS SEC_ENTRY
QueryContextAttributesA(
    PCtxtHandle phContext,              // Context to query
    unsigned long ulAttribute,          // Attribute to query
    void SEC_FAR * pBuffer              // Buffer for attributes
    );

typedef SECURITY_STATUS
(SEC_ENTRY * QUERY_CONTEXT_ATTRIBUTES_FN_A)(
    PCtxtHandle,
    unsigned long,
    void SEC_FAR *);

#ifdef UNICODE
#define QueryContextAttributes QueryContextAttributesW
#define QUERY_CONTEXT_ATTRIBUTES_FN QUERY_CONTEXT_ATTRIBUTES_FN_W
#else
#define QueryContextAttributes QueryContextAttributesA
#define QUERY_CONTEXT_ATTRIBUTES_FN QUERY_CONTEXT_ATTRIBUTES_FN_A
#endif // !UNICODE

SECURITY_STATUS SEC_ENTRY
QueryCredentialsAttributesW(
    PCredHandle phCredential,           // Credential to query
    unsigned long ulAttribute,          // Attribute to query
    void SEC_FAR * pBuffer              // Buffer for attributes
    );

typedef SECURITY_STATUS
(SEC_ENTRY * QUERY_CREDENTIALS_ATTRIBUTES_FN_W)(
    PCredHandle,
    unsigned long,
    void SEC_FAR *);

SECURITY_STATUS SEC_ENTRY
QueryCredentialsAttributesA(
    PCredHandle phCredential,           // Credential to query
    unsigned long ulAttribute,          // Attribute to query
    void SEC_FAR * pBuffer              // Buffer for attributes
    );

typedef SECURITY_STATUS
(SEC_ENTRY * QUERY_CREDENTIALS_ATTRIBUTES_FN_A)(
    PCredHandle,
    unsigned long,
    void SEC_FAR *);

#ifdef UNICODE
#define QueryCredentialsAttributes QueryCredentialsAttributesW
#define QUERY_CREDENTIALS_ATTRIBUTES_FN QUERY_CREDENTIALS_ATTRIBUTES_FN_W
#else
#define QueryCredentialsAttributes QueryCredentialsAttributesA
#define QUERY_CREDENTIALS_ATTRIBUTES_FN QUERY_CREDENTIALS_ATTRIBUTES_FN_A
#endif // !UNICODE

SECURITY_STATUS SEC_ENTRY
FreeContextBuffer(
    void SEC_FAR * pvContextBuffer              // buffer to free
    );

typedef SECURITY_STATUS
(SEC_ENTRY * FREE_CONTEXT_BUFFER_FN)(
    void SEC_FAR *);

///////////////////////////////////////////////////////////////////
////
////    Message Support API
////
//////////////////////////////////////////////////////////////////

SECURITY_STATUS SEC_ENTRY
MakeSignature(
    PCtxtHandle phContext,              // Context to use
    unsigned long fQOP,                 // Quality of Protection
    PSecBufferDesc pMessage,            // Message to sign
    unsigned long MessageSeqNo          // Message Sequence Num.
    );

typedef SECURITY_STATUS
(SEC_ENTRY * MAKE_SIGNATURE_FN)(
    PCtxtHandle,
    unsigned long,
    PSecBufferDesc,
    unsigned long);

SECURITY_STATUS SEC_ENTRY
VerifySignature(
    PCtxtHandle phContext,              // Context to use
    PSecBufferDesc pMessage,            // Message to verify
    unsigned long MessageSeqNo,         // Sequence Num.
    unsigned long SEC_FAR * pfQOP               // QOP used
    );

typedef SECURITY_STATUS
(SEC_ENTRY * VERIFY_SIGNATURE_FN)(
    PCtxtHandle,
    PSecBufferDesc,
    unsigned long,
    unsigned long SEC_FAR *);

SECURITY_STATUS SEC_ENTRY
EncryptMessage( PCtxtHandle         phContext,
                unsigned long       fQOP,
                PSecBufferDesc      pMessage,
                unsigned long       MessageSeqNo);

typedef SECURITY_STATUS
(SEC_ENTRY * ENCRYPT_MESSAGE_FN)(
    PCtxtHandle, unsigned long, PSecBufferDesc, unsigned long);


SECURITY_STATUS SEC_ENTRY
DecryptMessage( PCtxtHandle         phContext,
                PSecBufferDesc      pMessage,
                unsigned long       MessageSeqNo,
                unsigned long *     pfQOP);
	

typedef SECURITY_STATUS
(SEC_ENTRY * DECRYPT_MESSAGE_FN)(
    PCtxtHandle, PSecBufferDesc, unsigned long,
    unsigned long SEC_FAR *);

SECURITY_STATUS SEC_ENTRY
SealMessage( PCtxtHandle         phContext,
                unsigned long       fQOP,
                PSecBufferDesc      pMessage,
                unsigned long       MessageSeqNo);

typedef SECURITY_STATUS
(SEC_ENTRY * SEAL_MESSAGE_FN)(
    PCtxtHandle, unsigned long, PSecBufferDesc, unsigned long);


SECURITY_STATUS SEC_ENTRY
UnsealMessage( PCtxtHandle         phContext,
                PSecBufferDesc      pMessage,
                unsigned long       MessageSeqNo,
                unsigned long *     pfQOP);
	

typedef SECURITY_STATUS
(SEC_ENTRY * UNSEAL_MESSAGE_FN)(
    PCtxtHandle, PSecBufferDesc, unsigned long,
    unsigned long SEC_FAR *);

///////////////////////////////////////////////////////////////////////////
////
////    Misc.
////
///////////////////////////////////////////////////////////////////////////

SECURITY_STATUS SEC_ENTRY
EnumerateSecurityPackagesW(
    unsigned long SEC_FAR * pcPackages,     // Receives num. packages
    PSecPkgInfoW SEC_FAR * ppPackageInfo    // Receives array of info
    );

typedef SECURITY_STATUS
(SEC_ENTRY * ENUMERATE_SECURITY_PACKAGES_FN_W)(
    unsigned long SEC_FAR *,
    PSecPkgInfoW SEC_FAR *);

SECURITY_STATUS SEC_ENTRY
EnumerateSecurityPackagesA(
    unsigned long SEC_FAR * pcPackages,     // Receives num. packages
    PSecPkgInfoA SEC_FAR * ppPackageInfo    // Receives array of info
    );

typedef SECURITY_STATUS
(SEC_ENTRY * ENUMERATE_SECURITY_PACKAGES_FN_A)(
    unsigned long SEC_FAR *,
    PSecPkgInfoA SEC_FAR *);

#ifdef UNICODE
#define EnumerateSecurityPackages EnumerateSecurityPackagesW
#define ENUMERATE_SECURITY_PACKAGES_FN ENUMERATE_SECURITY_PACKAGES_FN_W
#else
#define EnumerateSecurityPackages EnumerateSecurityPackagesA
#define ENUMERATE_SECURITY_PACKAGES_FN ENUMERATE_SECURITY_PACKAGES_FN_A
#endif // !UNICODE

SECURITY_STATUS SEC_ENTRY
QuerySecurityPackageInfoW(
    SEC_WCHAR SEC_FAR * pszPackageName,     // Name of package
    PSecPkgInfoW SEC_FAR *ppPackageInfo     // Receives package info
    );

typedef SECURITY_STATUS
(SEC_ENTRY * QUERY_SECURITY_PACKAGE_INFO_FN_W)(
    SEC_WCHAR SEC_FAR *,
    PSecPkgInfoW SEC_FAR *);

SECURITY_STATUS SEC_ENTRY
QuerySecurityPackageInfoA(
    SEC_CHAR SEC_FAR * pszPackageName,     // Name of package
    PSecPkgInfoA SEC_FAR *ppPackageInfo     // Receives package info
    );

typedef SECURITY_STATUS
(SEC_ENTRY * QUERY_SECURITY_PACKAGE_INFO_FN_A)(
    SEC_CHAR SEC_FAR *,
    PSecPkgInfoA SEC_FAR *);

#ifdef UNICODE
#define QuerySecurityPackageInfo QuerySecurityPackageInfoW
#define QUERY_SECURITY_PACKAGE_INFO_FN QUERY_SECURITY_PACKAGE_INFO_FN_W
#else
#define QuerySecurityPackageInfo QuerySecurityPackageInfoA
#define QUERY_SECURITY_PACKAGE_INFO_FN QUERY_SECURITY_PACKAGE_INFO_FN_A
#endif // !UNICODE

typedef enum _SecDelegationType {
    SecFull,
    SecService,
    SecTree,
    SecDirectory,
    SecObject
} SecDelegationType, * PSecDelegationType;

SECURITY_STATUS SEC_ENTRY
DelegateSecurityContext(
    PCtxtHandle         phContext,          // IN Active context to delegate
    LPWSTR              pszTarget,
    SecDelegationType   DelegationType,     // IN Type of delegation
    PTimeStamp          pExpiry,            // IN OPTIONAL time limit
    PSecBuffer          pPackageParameters, // IN OPTIONAL package specific
    PSecBufferDesc      pOutput);           // OUT Token for applycontroltoken.

///////////////////////////////////////////////////////////////////////////
////
////    Proxies
////
///////////////////////////////////////////////////////////////////////////

//
// Proxies are only available on Microsoft Windows NT platforms
//

///////////////////////////////////////////////////////////////////////////////
////
////  Fast access for RPC:
////
///////////////////////////////////////////////////////////////////////////////

#define SECURITY_ENTRYPOINTW SEC_TEXT("InitSecurityInterfaceW")
#define SECURITY_ENTRYPOINTA SEC_TEXT("InitSecurityInterfaceA")

#ifdef UNICODE
#define SECURITY_ENTRYPOINT SECURITY_ENTRYPOINTW
#else // UNICODE
#define SECURITY_ENTRYPOINT SECURITY_ENTRYPOINTA
#endif // UNICODE

#define FreeCredentialHandle FreeCredentialsHandle

typedef struct _SECURITY_FUNCTION_TABLE_W {
    unsigned long                       dwVersion;
    ENUMERATE_SECURITY_PACKAGES_FN_W    EnumerateSecurityPackagesW;
    QUERY_CREDENTIALS_ATTRIBUTES_FN_W   QueryCredentialsAttributesW;
    ACQUIRE_CREDENTIALS_HANDLE_FN_W     AcquireCredentialsHandleW;
    FREE_CREDENTIALS_HANDLE_FN          FreeCredentialsHandle;
    void SEC_FAR *                      Reserved2;
    INITIALIZE_SECURITY_CONTEXT_FN_W    InitializeSecurityContextW;
    ACCEPT_SECURITY_CONTEXT_FN          AcceptSecurityContext;
    COMPLETE_AUTH_TOKEN_FN              CompleteAuthToken;
    DELETE_SECURITY_CONTEXT_FN          DeleteSecurityContext;
    APPLY_CONTROL_TOKEN_FN              ApplyControlToken;
    QUERY_CONTEXT_ATTRIBUTES_FN_W       QueryContextAttributesW;
    IMPERSONATE_SECURITY_CONTEXT_FN     ImpersonateSecurityContext;
    REVERT_SECURITY_CONTEXT_FN          RevertSecurityContext;
    MAKE_SIGNATURE_FN                   MakeSignature;
    VERIFY_SIGNATURE_FN                 VerifySignature;
    FREE_CONTEXT_BUFFER_FN              FreeContextBuffer;
    QUERY_SECURITY_PACKAGE_INFO_FN_W    QuerySecurityPackageInfoW;
    void SEC_FAR *                      Reserved3;
    void SEC_FAR *                      Reserved4;
    void SEC_FAR *                      Reserved5;
    void SEC_FAR *                      Reserved6;
    void SEC_FAR *                      Reserved7;
    void SEC_FAR *                      Reserved8;
    QUERY_SECURITY_CONTEXT_TOKEN_FN     QuerySecurityContextToken;
    ENCRYPT_MESSAGE_FN                  EncryptMessage;
    DECRYPT_MESSAGE_FN                  DecryptMessage;
} SecurityFunctionTableW, SEC_FAR * PSecurityFunctionTableW;

typedef struct _SECURITY_FUNCTION_TABLE_A {
    unsigned long                       dwVersion;
    ENUMERATE_SECURITY_PACKAGES_FN_A    EnumerateSecurityPackagesA;
    QUERY_CREDENTIALS_ATTRIBUTES_FN_A   QueryCredentialsAttributesA;
    ACQUIRE_CREDENTIALS_HANDLE_FN_A     AcquireCredentialsHandleA;
    FREE_CREDENTIALS_HANDLE_FN          FreeCredentialHandle;
    void SEC_FAR *                      Reserved2;
    INITIALIZE_SECURITY_CONTEXT_FN_A    InitializeSecurityContextA;
    ACCEPT_SECURITY_CONTEXT_FN          AcceptSecurityContext;
    COMPLETE_AUTH_TOKEN_FN              CompleteAuthToken;
    DELETE_SECURITY_CONTEXT_FN          DeleteSecurityContext;
    APPLY_CONTROL_TOKEN_FN              ApplyControlToken;
    QUERY_CONTEXT_ATTRIBUTES_FN_A       QueryContextAttributesA;
    IMPERSONATE_SECURITY_CONTEXT_FN     ImpersonateSecurityContext;
    REVERT_SECURITY_CONTEXT_FN          RevertSecurityContext;
    MAKE_SIGNATURE_FN                   MakeSignature;
    VERIFY_SIGNATURE_FN                 VerifySignature;
    FREE_CONTEXT_BUFFER_FN              FreeContextBuffer;
    QUERY_SECURITY_PACKAGE_INFO_FN_A    QuerySecurityPackageInfoA;
    void SEC_FAR *                      Reserved3;
    void SEC_FAR *                      Reserved4;
    void SEC_FAR *                      Reserved5;
    void SEC_FAR *                      Reserved6;
    void SEC_FAR *                      Reserved7;
    void SEC_FAR *                      Reserved8;
    QUERY_SECURITY_CONTEXT_TOKEN_FN     QuerySecurityContextToken;
    ENCRYPT_MESSAGE_FN                  EncryptMessage;
    DECRYPT_MESSAGE_FN                  DecryptMessage;
} SecurityFunctionTableA, SEC_FAR * PSecurityFunctionTableA;

#ifdef UNICODE
#define SecurityFunctionTable SecurityFunctionTableW
#define PSecurityFunctionTable PSecurityFunctionTableW
#else
#define SecurityFunctionTable SecurityFunctionTableA
#define PSecurityFunctionTable PSecurityFunctionTableA
#endif // !UNICODE

#define SECURITY_

#define SECURITY_SUPPORT_PROVIDER_INTERFACE_VERSION     1

PSecurityFunctionTableA SEC_ENTRY
InitSecurityInterfaceA(
    void
    );

typedef PSecurityFunctionTableA
(SEC_ENTRY * INIT_SECURITY_INTERFACE_A)(void);

PSecurityFunctionTableW SEC_ENTRY
InitSecurityInterfaceW(
    void
    );

typedef PSecurityFunctionTableW
(SEC_ENTRY * INIT_SECURITY_INTERFACE_W)(void);

#ifdef UNICODE
#define InitSecurityInterface InitSecurityInterfaceW
#define INIT_SECURITY_INTERFACE INIT_SECURITY_INTERFACE_W
#else
#define InitSecurityInterface InitSecurityInterfaceA
#define INIT_SECURITY_INTERFACE INIT_SECURITY_INTERFACE_A
#endif // !UNICODE

#ifdef __cplusplus
}  // extern "C"
#endif

#endif // __SSPI_H__
