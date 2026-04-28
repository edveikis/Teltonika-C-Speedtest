# Teltonika-c-speedtest

Simple CLI application that measures internet speeds.

Features:
* Measures upload speed
* Measures download speed
* Finds the best server from the list using users location

Built using:
* libcurl
* cJSON
* getopt

## ⚠️ IMPORTANT

This repo does not contain `speedtest_server_list.json`. Please add it yourself or find best server and full auto test functions wont work.

## Dependencies

* libcurl

```bash
sudo dnf install libcurl-devel
```

## Building

1. Clone repo

```bash
git clone https://github.com/edveikis/Teltonika-C-Speedtest.git
```

2. cd into it

```bash
cd Teltonika-C-Speedtest
```

3. Build it using `make`

```bash
make
```

## Usage

```bash
./bin/speedtest [OPTIONS]
```

### Options

1. Full automatic test

```bash
./bin/speedtest -a
```

2. Find best server

```bash
./bin/speedtest -b
```

3. Download test

```bash
./bin/speedtest -d http://example.com
```

4. Upload test

```bash
./bin/speedtest -u http://example.com
```

NOTE: Download and upload can be used in one go.
