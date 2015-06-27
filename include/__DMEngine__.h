#ifndef __20150610___DMENIGNE___H
#define __20150610___DMENIGNE___H
namespace DMEngine{
class LOG{
	LOG(const LOG&) = delete;
	LOG(LOG&&) = delete;
	LOG() = delete;
public:
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
	Log(const Log&) = delete;
	Log(Log&&) = delete;
	Log() = delete;
public:
	~Log();
	int operator()(const char*, ...) const;
	const LOG operator()() const;
};
extern const Log& log;
}
namespace DME = DMEngine;
#endif