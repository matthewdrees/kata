import logging
import sys
import struct

def rshift(val, n):
    if val > 0:
        return val >> n
    elif n > 0:
        n -= 1
        newval = val >> 1
        newval = newval - 0x80000000
        return newval >> n

    return val

def a(val, offset, size):
    return rshift(val, offset) % 2**size

def dataProcessingRegisterShift(cond, word):
    logging.info("Data processing register shift.")

    opcode = a(word, 21, 4)
    s = a(word, 20, 1)
    rn = a(word, 16, 4)
    rd = a(word, 12, 4)
    rs = a(word, 8, 4)
    shift = a(word, 5, 2)
    rm = a(word, 0, 4)
    logging.info("cond: %#x: opcode: %#x, s: %d, Rn: %#x, Rd: %#x, rs: %#x, shift: %#x, rm: %#x" % (cond,
                                                                                                    opcode,
                                                                                                    s,
                                                                                                    rn,
                                                                                                    rd,
                                                                                                    rs,
                                                                                                    shift,
                                                                                                    rm))
    if opcode == 0b1101:
        return "mov r%d,r%d" % (rd, rs)
    else:
        logging.error("unhandled opcode %d" % opcode)

    return ""


def dataProcessingImmediate(cond, word):
    logging.info("Data processing immediate.")

    opcode = a(word, 21, 4)
    s = a(word, 20, 1)
    rn = a(word, 16, 4)
    rd = a(word, 12, 4)
    rot = a(word, 8, 4)
    immed = a(word, 0, 8)
    logging.info("cond: %#x: opcode: %#x, s: %d, Rn: %#x, Rd: %#x, rot: %#x, immed: %#x" % (cond,
                                                                                            opcode,
                                                                                            s,
                                                                                            rn,
                                                                                            rd,
                                                                                            rot,
                                                                                            immed))
    if opcode == 0b1101:
        return "mov r%d,#%d" % (rd, immed << rot)
    else:
        logging.error("unhandled opcode %d" % opcode)

    return ""

def loadStoreImmediateOffset(cond, word):
    logging.info("Load/store immediate offset.")

    p = a(word, 24, 1)
    u = a(word, 23, 1)
    b = a(word, 22, 1)
    w = a(word, 21, 1)
    l = a(word, 20, 1)
    rn = a(word, 16, 4)
    rd = a(word, 12, 4)
    immed = a(word, 0, 12)
    logging.info("cond: %#x: p: %d, u: %d, b: %d, w: %d, l: %d, rn: %#x, rd: %#x, immed: %#x" % (cond,
                                                                                                 p,
                                                                                                 u,
                                                                                                 b,
                                                                                                 w,
                                                                                                 l,
                                                                                                 rn,
                                                                                                 rd,
                                                                                                 immed))
    return "str r%d,r[%d]" % (rd, rn)

def main(fn):
    fin = open(fn, "rb")

    for x in xrange(3):
        word = struct.unpack('i', fin.read(4))[0]
        logging.debug("word: %d" % word)
        cond = rshift(word, 28) % 2**4
        op = rshift(word, 25) % 2**3
        if op == 0b000:
            assemStr = dataProcessingRegisterShift(cond, word)
        elif op == 0b001:
            assemStr = dataProcessingImmediate(cond, word)
        elif op == 0b010:
            assemStr = loadStoreImmediateOffset(cond, word)
        else:
            logging.error("unhandled op %d" % op)

        print assemStr

if __name__ == "__main__":
    logging.basicConfig(level=logging.DEBUG)
    main("hello.bin")


