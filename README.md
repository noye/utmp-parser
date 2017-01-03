# utmp-parser
This tool is a binary for Windows that will help you check the utmp information in linux.

## build
* This tool was developed as a visual studio 2015 professional and was developed to support at least visual studio 2010.

## usage
* utmpx.exe [file_path]

### example
```
C:\test>utmpx.exe C:\Users\Owner\Desktop\utmp
[type] : BOOT_TIME
[user] : reboot
[host] : 4.4.0-57-generic
[time] : Sun Jan 01 20:15:30 2017


[type] : RUN_LVL
[user] : runlevel
[host] : 4.4.0-57-generic
[time] : Sun Jan 01 20:15:32 2017


[type] : LOGIN_PROCESS
[pid]  : 1487
[line] : tty1
[user] : LOGIN
[host] :
[time] : Sun Jan 01 20:15:32 2017


[type] : USER_PROCESS
[pid]  : 1906
[line] : tty7
[user] : noye
[host] : :0
[time] : Sun Jan 01 20:15:51 2017
```
