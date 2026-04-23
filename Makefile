all: SysCPURead/CPURead.o SysStoRead/StoRead.o Tools/Tools.o SysMemRead/MemRead.o SysNetRead/NetRead.o

SysCPURead/CPURead.o: SysCPURead/CPURead.c SysCPURead/CPURead.h
	gcc -Wall -Wextra -Werror -std=c11 -c SysCPURead/CPURead.c -o SysCPURead/CPURead.o

SysStoRead/StoRead.o: SysStoRead/StoRead.c SysStoRead/StoRead.h
	gcc -Wall -Wextra -Werror -std=c11 -c SysStoRead/StoRead.c -o SysStoRead/StoRead.o

Tools/Tools.o: Tools/Tools.c Tools/Tools.h
	gcc -Wall -Wextra -Werror -std=c11 -c Tools/Tools.c -o Tools/Tools.o

SysMemRead/MemRead.o: SysMemRead/MemRead.c SysMemRead/MemRead.h
	gcc -Wall -Wextra -Werror -std=c11 -c SysMemRead/MemRead.c -o SysMemRead/MemRead.o

SysNetRead/NetRead.o: SysNetRead/NetRead.c SysNetRead/NetRead.h
	gcc -Wall -Wextra -Werror -std=c11 -c SysNetRead/NetRead.c -o SysNetRead/NetRead.o

nettoyage:
	rm -f SysCPURead/CPURead.o SysStoRead/StoRead.o Tools/Tools.o SysMemRead/MemRead.o SysNetRead/NetRead.o

reconstruction:
	make nettoyage
	make