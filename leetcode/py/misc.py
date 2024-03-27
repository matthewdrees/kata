# Misc helper code


def sum_of_continuous_numbers(lo: int, hi: int):
    """Sum of a run of numbers, from low to high."""
    assert lo <= hi
    # Carl Gauss equation.
    return int((hi - lo + 1) / 2 * (lo + hi))


def test_sum_of_continuous_numbers():
    test_cases = (
        (1, 1, 1),
        (2, 2, 2),
        (3, 3, 3),
        (1, 2, 3),
        (1, 3, 6),
        (2, 3, 5),
        (1, 4, 10),
        (2, 4, 9),
        (3, 5, 12),
        (3, 4, 7),
        (11, 20, 155),
        (1, 50, 1275),
        (1, 100, 5050),
    )
    for lo, hi, exp in test_cases:
        act = sum_of_continuous_numbers(lo, hi)
        if exp != act:
            print(
                f"{test_sum_of_continuous_numbers.__name__}, fail, lo: {lo}, hi: {hi}, exp: {exp}, act: {act}"
            )


if __name__ == "__main__":
    test_sum_of_continuous_numbers()
