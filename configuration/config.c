#include "config.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static Config defaultConfig = {
    2 * 1000,
    3 * 1000,
    4 * 1000,
    "/tmp/tc/receive.sock",
    "/tmp/tc/send.sock",
    "/tmp/tc/sense.sock",
    "/tmp/tc/flash.dat"
};

static Config userConfig;

static void loadDefaultConfig()
{
	memcpy(&userConfig, &defaultConfig, sizeof(Config));
}

static void usage()
{
    fprintf(stderr, 
		"valid options: [-h] [-c dt_collect=%d] [-r dt_receive=%d] [-s dt_send=%d] [-i fn_receive='%s'] [-o fn_send='%s'] [-e fn_sense='%s'] [-f fn_flash='%s']\n", 
		defaultConfig.dt_collect, defaultConfig.dt_receive, defaultConfig.dt_send, defaultConfig.fn_receive, defaultConfig.fn_send, defaultConfig.fn_sense, defaultConfig.fn_flash);
	exit(1);
}

int parseNumber(char* number)
{
	char* endptr;
	int res = strtol(number, &endptr, 10);
	if (endptr[0] == '\0') return res;
	usage();
}

const Config* parseOptions(int argc, char** argv)
{
	loadDefaultConfig();
	const char* options = "hc:r:s:i:o:e:f:";

	int opt;

	while ((opt = getopt(argc, argv, options)) != -1) {
		switch (opt) {
			case 'h': usage();
			case 'c': userConfig.dt_collect = parseNumber(optarg); break;
			case 'r': userConfig.dt_receive = parseNumber(optarg); break;
			case 's': userConfig.dt_send = parseNumber(optarg); break;
			case 'i': userConfig.fn_receive = optarg; break;
			case 'o': userConfig.fn_send = optarg; break;
			case 'e': userConfig.fn_sense = optarg; break;
			case 'f': userConfig.fn_flash = optarg; break;
			default: usage();
		}
	}

    return &userConfig;
}
