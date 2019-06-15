#include "signal.hpp"
#include <signal.h>
#include <string>
#include <thread>
#include <chrono>

// Blog: https://blog.csdn.net/fengbingchun/article/details/92074191

namespace signal_ {

namespace {

bool flag = true;

void process_exit(int sig)
{
	switch (sig) {
		case SIGINT:
			fprintf(stderr, "process exit: SIGINT: value: %d\n", sig);
			break;
		case SIGFPE:
			fprintf(stderr, "process exit: SIGFPE: value: %d\n", sig);
			break;
		case SIGABRT:
			fprintf(stderr, "process exit: SIGABRT: value: %d\n", sig);
			break;
		case SIGILL:
			fprintf(stderr, "process exit: SIGILL: value: %d\n", sig);
			break;
		case SIGSEGV:
			fprintf(stderr, "process exit: SIGSEGV: value: %d\n", sig);
			break;
		case SIGTERM:
			fprintf(stderr, "process exit: SIGTERM: value: %d\n", sig);
			break;
		default:
			fprintf(stderr, "process exit: value: %d\n", sig);
			break;
	}

	flag = false;
}

void wait_ctrl_c()
{
	while (flag) {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		fprintf(stdout, "please press to exit: Ctrl + c ... \n");
	}
}

void signal_type()
{
	signal(SIGINT, process_exit);
	signal(SIGFPE, process_exit);
	signal(SIGILL, process_exit);
	signal(SIGABRT, process_exit);
	signal(SIGSEGV, process_exit);
	signal(SIGTERM, process_exit);
}

void signal_sigill(int)
{
	fprintf(stdout, "caught SIGILL signal\n");
}

void signal_sigterm(int)
{
	fprintf(stdout, "caught SIGTERM signal\n");
}

} // namespace

int test_signal_SIGINT()
{
	signal_type();

	std::thread th(wait_ctrl_c);
	th.join();

	return 0;
}

int test_signal_SIGILL()
{
	//signal_type();

	if (signal(SIGILL, signal_sigill) == SIG_ERR) {
		fprintf(stdout, "cannot handle SIGILL\n");
	} else {
		fprintf(stdout, "yyyyy\n");
	}

	return 0;
}

int test_signal_SIGFPE()
{
	signal_type();

	int a = 1, b = 0, c;
	c = a / b;
	fprintf(stdout, "c = %d\n", c);

	return 0;
}

int test_signal_SIGSEGV()
{
	signal_type();
	
	int a[3] = {0};
	fprintf(stdout, "a[3] = %d\n", a[-1111111]);
	
	return 0;
}

int test_signal_SIGTERM()
{
	//signal_type();

	if (signal(SIGTERM, signal_sigterm) == SIG_ERR) {
		fprintf(stdout, "cannot handle SIGTERM\n");
	} else {
		fprintf(stdout, "xxxxx\n");
	}


	return 0;
}

int test_signal_SIGABRT()
{
	signal_type();

	abort();

	return 0;
}

} // namespace signal_
