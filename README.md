# log_parser

Program for parsing text log files having rows of the following format:

```
<host name> [DD:HH:MM:SS] "<request URI>" <HTTP return code> <return bytes>
```

The program prints 2 sets of statistics from the log file:
- count of requests made per unique host name, sorted in decreasing order by count
- count of successful GET requests per unique URI, sorted in decreasing order by count

Optionally, the user may specify start and end time options to limit the entries selected.

## Use

Build using Cmake from the top level folder:
```
mkdir build
cd build 
cmake ..
make
```

To run, provide the following required and option command arguments:

```
./main -f <path_to_log_file> [-s] <start_time DD:HH:MM:SS> [-e] <end_time DD:HH:MM:SS>
```