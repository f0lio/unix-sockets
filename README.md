# UNIX Sockets

### Practicing Socket programming by making a simple server in C.

### Usage:
Compile and run the server (You can specify any* port you want):
```shell
$ make && ./server 8080
```

Test it using `telnet`:
```shell
$ telnet localhost 8080
```
or using `cURL`:

```shell
$ curl --http0.9 -v localhost:8080
```
 `--http0.9` tells cURL to handle HTTP/0.9 response normally.
<br>
`-v` for verbose mode.


***P.S:*** Port is better not be less than 1024, as those are reserved already, plus normal users are not allowed to run servers on them; thus causing an error when binding the socket (unless you run the server as root).
