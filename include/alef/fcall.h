#define	VERSION9P	"9P2000"
#define	MAXWELEM	16

aggr Fcall
{
	byte	type;
	uint	fid;
	usint	tag;
	uint	msize;	/* Tversion, Rversion */
	byte	 * version;	/* Tversion, Rversion */
	usint	oldtag;	/* Tflush */
	byte	 * ename;		/* Rerror */
	Qid	qid;	/* Rattach, Ropen, Rcreate */
	uint	iounit;	/* Ropen, Rcreate */
	Qid	aqid;	/* Rauth */
	uint	afid;	/* Tauth, Tattach */
	byte	 * uname;	/* Tauth, Tattach */
	byte	 * aname;	/* Tauth, Tattach */
	uint	perm;	/* Tcreate */
	byte	 * name;	/* Tcreate */
	byte	mode;	/* Tcreate, Topen */
	uint	newfid;	/* Twalk */
	usint	nwname;	/* Twalk */
	byte	 * wname[MAXWELEM];	/* Twalk */
	usint	nwqid;	/* Rwalk */
	Qid	wqid[MAXWELEM];	/* Rwalk */
	int	offset[2];	/* Tread, Twrite */
	uint	count;	/* Tread, Twrite, Rread */
	byte	 * data;	/* Twrite, Rread */
	usint	nstat;	/* Twstat, Rstat */
	byte	 * stat;	/* Twstat, Rstat */
	int	unixfd;	/* Ropenfd */

	/* 9P2000.u extensions */
	int	errornum;	/* Rerror */
	int	uidnum;	/* Tattach, Tauth */
	byte	 * extension;	/* Tcreate */
};


#define	GBIT8(p)	((p)[0])
#define	GBIT16(p)	((p)[0]|((p)[1]<<8))
#define	GBIT32(p)	((uint)((p)[0]|((p)[1]<<8)|((p)[2]<<16)|((p)[3]<<24)))
#define	GBIT64(p)	((uint)((p)[4]|((p)[5]<<8)|((p)[6]<<16)|((p)[7]<<24)), (uint)((p)[0]|((p)[1]<<8)|((p)[2]<<16)|((p)[3]<<24)))

#define	PBIT8(p,v)	(p)[0]=(v)
#define	PBIT16(p,v)	(p)[0]=(v);(p)[1]=(v)>>8
#define	PBIT32(p,v)	(p)[0]=(v);(p)[1]=(v)>>8;(p)[2]=(v)>>16;(p)[3]=(v)>>24
#define	PBIT64(p,v)	(p)[0]=(v[0]);(p)[1]=(v[0])>>8;(p)[2]=(v[0])>>16;(p)[3]=(v[0])>>24;\
			(p)[4]=(v[1]);(p)[5]=(v[1])>>8;(p)[6]=(v[1])>>16;(p)[7]=(v[1])>>24

#define	BIT8SZ		1
#define	BIT16SZ		2
#define	BIT32SZ		4
#define	BIT64SZ		8
#define	QIDSZ	(BIT8SZ+BIT32SZ+BIT64SZ)

/* STATFIXLEN includes leading 16-bit count */
/* The count, however, excludes itself; total size is BIT16SZ+count */
#define STATFIXLEN	(BIT16SZ+QIDSZ+5*BIT16SZ+4*BIT32SZ+1*BIT64SZ)	/* amount of fixed length data in a stat buffer */
#define STATFIXLENU	(STATFIXLEN+BIT16SZ+3*BIT32SZ)	/* for 9P2000.u */

#define	NOTAG		(ushort)~0U	/* Dummy tag */
#define	NOFID		(uint)~0U	/* Dummy fid */
#define	NOUID		(-1)	/* Dummy uid */
#define	IOHDRSZ		24	/* ample room for Twrite/Rread header (iounit) */

enum
{
	Tversion = 	100,
	    Rversion,
	    Tauth = 		102,
	    Rauth,
	    Tattach = 	104,
	    Rattach,
	    Terror = 	106, 	/* illegal */
	Rerror,
	    Tflush = 	108,
	    Rflush,
	    Twalk = 		110,
	    Rwalk,
	    Topen = 		112,
	    Ropen,
	    Tcreate = 	114,
	    Rcreate,
	    Tread = 		116,
	    Rread,
	    Twrite = 	118,
	    Rwrite,
	    Tclunk = 	120,
	    Rclunk,
	    Tremove = 	122,
	    Rremove,
	    Tstat = 		124,
	    Rstat,
	    Twstat = 	126,
	    Rwstat,
	    Tmax,

	    Topenfd = 	98,
	    Ropenfd
};
uint	convM2S(byte*, uint, Fcall*);
uint	convS2M(Fcall*, byte*, uint);
uint	sizeS2M(Fcall*);

int	statcheck(byte *abuf, uint nbuf);
uint	convM2D(byte*, uint, Dir*, byte*);
uint	convD2M(Dir*, byte*, uint);
uint	sizeD2M(Dir*);

int	fcallconv(Printspec*);
int	dirconv(Printspec*);
int	dirmodeconv(Printspec*);
