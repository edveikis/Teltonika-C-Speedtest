#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

#include "cJSON.h"
#include "dataImporter.h"
#include "httpClient.h"
#include "locationService.h"
#include "speedTest.h"

int main(int argc, char *argv[]) 
{
    speed_test_download("http://speedtest.tele2.net/100MB.zip", 0);

    return 0;
}
