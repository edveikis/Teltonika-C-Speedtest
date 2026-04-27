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
    speed_test_upload("speed-kaunas.telia.lt:8080", 100);

    return 0;
}
