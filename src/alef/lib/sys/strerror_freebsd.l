#include <alef.h>

#define _STANDALONE
#include <errno.h>

intern byte *_error_strings[] = {
	"Operation not permitted",
	    "No such file or directory",
	    "No such process",
	    "Interrupted system call",
	    "Input/output error",
	    "Device not configured",
	    "Argument list too long",
	    "Exec format error",
	    "Bad file descriptor",
	    "No child processes",
	    "Resource deadlock avoided",
	    "11 was EAGAIN", /* LOL. */
	"Cannot allocate memory",
	    "Permission denied",
	    "Bad address",
	    "Block device required",
	    "Device busy",
	    "File exists",
	    "Cross-device link",
	    "Operation not supported by device",
	    "Not a directory",
	    "Is a directory",
	    "Invalid argument",
	    "Too many open files in system",
	    "Too many open files",
	    "Inappropriate ioctl for device",
	    "Text file busy",
	    "File too large",
	    "No space left on device",
	    "Illegal seek",
	    "Read-only filesystem",
	    "Too many links",
	    "Broken pipe",

	    /* math software */
	"Numerical argument out of domain",
	    "Result too large",

	    /* non-blocking and interrupt i/o */
	"Operation would block",
	    "Operation now in progress",
	    "Operation already in progress",

	    /* ipc/network software -- argument errors */
	"Socket operation on non-socket",
	    "Destination address required",
	    "Message too long",
	    "Protocol wrong type for socket",
	    "Protocol not available",
	    "Protocol not supported",
	    "Socket type not supported",
	    "Operation not supported",
	    "Protocol family not supported",
	    "Address family not supported by protocol family",
	    "Address already in use",
	    "Can't assign requested address",

	    /* ipc/network software -- operational errors */
	"Network is down",
	    "Network is unreachable",
	    "Network dropped connection on reset",
	    "Software caused connection abort",
	    "Connection reset by peer",
	    "No buffer space available",
	    "Socket is already connected",
	    "Socket is not connected",
	    "Can't send after socket shutdown",
	    "Too many references: can't splice",
	    "Operation timed out",
	    "Connection refused",

	    "Too many levels of symbolic links",
	    "File name too long",

	    /* should be rearranged */
	"Host is down",
	    "No route to host",
	    "Directory not empty",

	    /* quotas & mush */
	"Too many processes",
	    "Too many users",
	    "Disc quota exceeded",

	    /* Network File System */
	"Stale NFS file handle",
	    "Too many levels of remote in path",
	    "RPC struct is bad",
	    "RPC version wrong",
	    "RPC prog. not avail",
	    "Program version wrong",
	    "Bad procedure for program",

	    "No locks available",
	    "Function not implemented",

	    "Inappropriate file type or format",
	    "Authentication error",
	    "Need authenticator",
	    "Identifier removed",
	    "No message of desired type",
	    "Value too large to be stored in data type",
	    "Operation canceled",
	    "Illegal byte sequence",
	    "Attribute not found",

	    "Programming error",

	    "Bad message",
	    "Multihop attempted",
	    "Link has been severed",
	    "Protocol error",

	    "Capabilities insufficient",
	    "Not permitted in capability mode",
	    "State not recoverable",
	    "Previous owner died",
	    "Integrity check failed",
};


byte *
strerror(int errno)
{
	if (errno == 0) {
		return "";
	} else if (errno < ELAST) {
		return _error_strings[errno];
	} else {
		return "<UNDEFINED ERROR>";
	}
}


