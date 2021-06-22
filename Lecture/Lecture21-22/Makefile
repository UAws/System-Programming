PORT1=11015

fdopen: 01_example_fdopen.c
	gcc $< -o Exe_FDOPEN
	./Exe_FDOPEN

popen: 02_example_popen.c
	gcc $< -o Exe_POPEN
	./Exe_POPEN

client: 03_socket_client.c
	gcc 03_socket_client.c -o Exe_Client
	./Exe_Client bernard-VirtualBox 13000

server: 03_socket_server.c
	gcc 03_socket_server.c -o Exe_Server
	./Exe_Server bernard-VirtualBox 13000

rwc: 04_rw_client.c
	gcc $< -o Exe_RW_Client
	./Exe_RW_Client bernard-VirtualBox 12000 testfolder

rws: 04_rw_server.c
	gcc $< -o Exe_RW_Server
	./Exe_RW_Server

webc: 05_web_client.c
	gcc $< -o Exe_Web_Client
	./Exe_Web_Client bernard-VirtualBox $(PORT1) testfolder

webs: 05_web_server.c
	gcc $< -o Exe_Web_Server
	./Exe_Web_Server $(PORT1)
