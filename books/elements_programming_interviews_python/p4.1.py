# Elements of Programming Interviews in Python, p4.1

import pyperf
import random


def parity_naive(x):
    """Return the parity of binary 1s in x. Naive implementation. (p24)"""
    result = 0
    while x:
        result ^= x & 1
        x >>= 1
    return result


def parity_clever_bit_trick(x):
    """Return the parity of binary 1s in x, using clever 'x & (x-1)' trick. (p25)"""
    result = 0
    while x:
        result ^= 1
        x &= x - 1  # Drops trailing zeros. Clever!
    return result


def parity_lookup_table(x):
    """Return the parity of binary 1s in x, using lookup table. (p26)"""
    parity_table = (
        0,  # 0b0000
        1,  # 0b0001
        1,  # 0b0010
        0,  # 0b0011
        1,  # 0b0100
        0,  # 0b0101
        0,  # 0b0110
        1,  # 0b0111
        1,  # 0b1000
        0,  # 0b1001
        0,  # 0b1010
        1,  # 0b1011
        0,  # 0b1100
        1,  # 0b1101
        1,  # 0b1110
        0,  # 0b1111
    )
    MASK_SIZE = 4
    BIT_MASK = 0xF
    result = 0
    while x:
        result ^= parity_table[x & BIT_MASK]
        x >>= MASK_SIZE
    return result


if __name__ == "__main__":

    tests = (
        (0b0, 0),
        (0b1, 1),
        (0b10, 1),
        (0b11, 0),
        (0b100, 1),
        (0b101, 0),
        (0b110, 0),
        (0b111, 1),
        (0b1000, 1),
        (0b1001, 0),
        (0b1010, 0),
        (0b1011, 1),
        (0b1100, 0),
        (0b1101, 1),
        (0b1110, 1),
        (0b1111, 0),
    )
    for x, exp in tests:
        act = parity_lookup_table(x)
        if exp != act:
            print(f"FAIL, x: {x}, exp: {exp}, act: {act}")

    random.seed(a=0)
    min_int = -(2 ** 31)
    max_int = 2 ** 31 - 1
    num = random.randint(min_int, max_int)
    # print(num)
    runner = pyperf.Runner()
    # runner.bench_func("parity_naive", parity_naive, num)
    # parity_naive: Mean +- std dev: 3.54 us +- 0.06 us

    # runner.bench_func("parity_clever", parity_clever_bit_trick, num)
    # parity_clever: Mean +- std dev: 1.53 us +- 0.03 us

    runner.bench_func("parity_lookup_table", parity_lookup_table, num)
    # parity_lookup_table: Mean +- std dev: 1.04 us +- 0.03 us