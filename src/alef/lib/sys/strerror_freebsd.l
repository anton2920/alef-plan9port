#include <alef.h>

#define _STANDALONE
#include <errno.h>

intern byte *_error_strings[] = {
	"",
	[EPERM]   " Operation not permitted ",
	[ENOENT]  " No such file or directory ",
	[ESRCH]   " No such process ",
	[EINTR]   " Interrupted system call ",
	[EIO]     " Input/output error ",
	[ENXIO]   " Device not configured ",
	[E2BIG]   " Argument list too long ",
	[ENOEXEC] " Exec format error ",
	[EBADF]   " Bad file descriptor ",
	[ECHILD]  " No child processes ",
	[EDEADLK] " Resource deadlock avoided ",
	/* 11 was EAGAIN */
	[ENOMEM]  " Cannot allocate memory ",
	[EACCES]  " Permission denied ",
	[EFAULT]  " Bad address ",
	[ENOTBLK] " Block device required ",
	[EBUSY]   " Device busy ",
	[EEXIST]  " File exists ",
	[EXDEV]   " Cross-device link ",
	[ENODEV]  " Operation not supported by device ",
	[ENOTDIR] " Not a directory ",
	[EISDIR]  " Is a directory ",
	[EINVAL]  " Invalid argument ",
	[ENFILE]  " Too many open files in system ",
	[EMFILE]  " Too many open files ",
	[ENOTTY]  " Inappropriate ioctl for device ",
	[ETXTBSY] " Text file busy ",
	[EFBIG]   " File too large ",
	[ENOSPC]  " No space left on device ",
	[ESPIPE]  " Illegal seek ",
	[EROFS]   " Read-only filesystem ",
	[EMLINK]  " Too many links ",
	[EPIPE]   " Broken pipe ",

	/* math software */
	[EDOM]   " Numerical argument out of domain ",
	[ERANGE] " Result too large ",

	/* non-blocking and interrupt i/o */
	[EAGAIN]      " Resource temporarily unavailable ",
	[EINPROGRESS] "Operation now in progress",
	[EALREADY]    "Operation already in progress",

	/* ipc/network software -- argument errors */
	[ENOTSOCK]        " Socket operation on non-socket ",
	[EDESTADDRREQ]    " Destination address required ",
	[EMSGSIZE]        " Message too long ",
	[EPROTOTYPE]      " Protocol wrong type for socket ",
	[ENOPROTOOPT]     " Protocol not available ",
	[EPROTONOSUPPORT] " Protocol not supported ",
	[ESOCKTNOSUPPORT] " Socket type not supported ",
	[EOPNOTSUPP]      " Operation not supported ",
	[EPFNOSUPPORT]    " Protocol family not supported ",
	[EAFNOSUPPORT]    " Address family not supported by protocol family ",
	[EADDRINUSE]      " Address already in use ",
	[EADDRNOTAVAIL]   " Can't assign requested address ",

	/* ipc/network software -- operational errors */
	[ENETDOWN]     " Network is down ",
	[ENETUNREACH]  " Network is unreachable ",
	[ENETRESET]    " Network dropped connection on reset ",
	[ECONNABORTED] " Software caused connection abort ",
	[ECONNRESET]   " Connection reset by peer ",
	[ENOBUFS]      " No buffer space available ",
	[EISCONN]      " Socket is already connected ",
	[ENOTCONN]     " Socket is not connected ",
	[ESHUTDOWN]    " Can't send after socket shutdown ",
	[ETOOMANYREFS] " Too many references: can't splice ",
	[ETIMEDOUT]    " Operation timed out ",
	[ECONNREFUSED] " Connection refused ",

	[ELOOP]        " Too many levels of symbolic links ",
	[ENAMETOOLONG] " File name too long ",

	/* should be rearranged */
	[EHOSTDOWN]    " Host is down ",
	[EHOSTUNREACH] " No route to host ",
	[ENOTEMPTY]    " Directory not empty ",

	/* quotas & mush */
	[EPROCLIM] " Too many processes ",
	[EUSERS]   " Too many users ",
	[EDQUOT]   " Disc quota exceeded ",

	/* Network File System */
	[ESTALE]        " Stale NFS file handle ",
	[EREMOTE]       " Too many levels of remote in path ",
	[EBADRPC]       " RPC struct is bad ",
	[ERPCMISMATCH]  " RPC version wrong ",
	[EPROGUNAVAIL]  " RPC prog. not avail ",
	[EPROGMISMATCH] " Program version wrong ",
	[EPROCUNAVAIL]  " Bad procedure for program ",

	[ENOLCK] " No locks available ",
	[ENOSYS] " Function not implemented ",

	[EFTYPE]    " Inappropriate file type or format ",
	[EAUTH]     " Authentication error ",
	[ENEEDAUTH] " Need authenticator ",
	[EIDRM]     " Identifier removed ",
	[ENOMSG]    " No message of desired type ",
	[EOVERFLOW] " Value too large to be stored in data type ",
	[ECANCELED] " Operation canceled ",
	[EILSEQ]    " Illegal byte sequence ",
	[ENOATTR]   " Attribute not found ",

	[EDOOFUS] " Programming error ",

	[EBADMSG]   " Bad message ",
	[EMULTIHOP] " Multihop attempted ",
	[ENOLINK]   " Link has been severed ",
	[EPROTO]    " Protocol error ",

	[ENOTCAPABLE]     " Capabilities insufficient ",
	[ECAPMODE]        " Not permitted in capability mode ",
	[ENOTRECOVERABLE] " State not recoverable ",
	[EOWNERDEAD]      " Previous owner died ",
	[EINTEGRITY]      " Integrity check failed ",
};


byte *
strerror(int errno)
{
	if ((errno >= 0) && (errno <= ELAST)) {
		return _error_strings[errno];
	}
	return "<UNKNOWN ERROR>";
}


