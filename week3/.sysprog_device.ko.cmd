cmd_/home/juho/System_Programming/week3/sysprog_device.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 -T ./scripts/module-common.lds  --build-id  -o /home/juho/System_Programming/week3/sysprog_device.ko /home/juho/System_Programming/week3/sysprog_device.o /home/juho/System_Programming/week3/sysprog_device.mod.o ;  true