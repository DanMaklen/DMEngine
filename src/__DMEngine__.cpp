#include <cstdio>
#include <cstdarg>
using namespace std;

namespace DMEngine{
class LOG{
public:
	LOG();
	LOG(const LOG&);
	~LOG();

	const LOG& operator<<(const char* const) const;
	const LOG& operator<<(const void* const) const;
	const LOG& operator<<(const char) const;
	const LOG& operator<<(const short) const;
	const LOG& operator<<(const int) const;
	const LOG& operator<<(const long) const;
	const LOG& operator<<(const long long) const;
	const LOG& operator<<(const unsigned char) const;
	const LOG& operator<<(const unsigned short) const;
	const LOG& operator<<(const unsigned int) const;
	const LOG& operator<<(const unsigned long) const;
	const LOG& operator<<(const unsigned long long) const;
	const LOG& operator<<(const float) const;
	const LOG& operator<<(const double) const;
	const LOG& operator<<(const long double) const;
};

class Log{
	friend class LOG;
	Log(const Log&) = delete;
	Log(Log&&) = delete;
	Log();
public:
	static Log& __GetInstance();
private:
	FILE* __file;
public:
	~Log();
	const LOG operator()() const;
	int operator()(const char*, ...) const;
};
const Log& log = Log::__GetInstance();

//LOG
LOG::LOG(){}
LOG::LOG(const LOG& cpy){}
LOG::~LOG(){fprintf(log.__file, "\n"); fflush(log.__file);}
const LOG& LOG::operator<<(const char* const val) const{fprintf(log.__file, "%s", val); return *this;}
const LOG& LOG::operator<<(const void* const val) const{fprintf(log.__file, "%p", val); return *this;}
const LOG& LOG::operator<<(const char val) const{fprintf(log.__file, "%c", val); return *this;}
const LOG& LOG::operator<<(const short val) const{fprintf(log.__file, "%hd", val); return *this;}
const LOG& LOG::operator<<(const int val) const{fprintf(log.__file, "%d", val); return *this;}
const LOG& LOG::operator<<(const long val) const{fprintf(log.__file, "%ld", val); return *this;}
const LOG& LOG::operator<<(const long long val) const{fprintf(log.__file, "%lld", val); return *this;}
const LOG& LOG::operator<<(const unsigned char val) const{fprintf(log.__file, "%c", val); return *this;}
const LOG& LOG::operator<<(const unsigned short val) const{fprintf(log.__file, "%hu", val); return *this;}
const LOG& LOG::operator<<(const unsigned int val) const{fprintf(log.__file, "%u", val); return *this;}
const LOG& LOG::operator<<(const unsigned long val) const{fprintf(log.__file, "%lu", val); return *this;}
const LOG& LOG::operator<<(const unsigned long long val) const{fprintf(log.__file, "%llu", val); return *this;}
const LOG& LOG::operator<<(const float val) const{fprintf(log.__file, "%f", val); return *this;}
const LOG& LOG::operator<<(const double val) const{fprintf(log.__file, "%lf", val); return *this;}
const LOG& LOG::operator<<(const long double val) const{fprintf(log.__file, "%Lf", val); return *this;}

//Log
Log& Log::__GetInstance(){static Log __inst; return __inst;}
Log::Log() : __file(fopen("DMEngine_Log.log", "a")){}
Log::~Log(){fclose(__file);}
const LOG Log::operator()() const{return LOG();}
int Log::operator()(const char * fmt, ...) const{
	va_list args;
	va_start(args, fmt);
	int ret = vfprintf(__file, fmt, args);
	va_end(args);
	fprintf(__file, "\n");
	fflush(__file);
	return ret;
}
}