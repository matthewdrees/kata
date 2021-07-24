# ProjectEuler problem 65. Convergents of e.
def genSeriesE():
    x = 1
    count = 0

    while 1:
        if count % 3 == 1:
            yield x * 2
        else:
            yield 1

        if count % 3 == 2:
            x += 1
        count += 1


def eFractions(stop):
    series = []
    convergent = 1

    for x in genSeriesE():
        #print(f"{convergent}, {x}")
        convergent += 1
        n = 1
        d = x
        series.append((n, d))
        if convergent == stop:
            break

    return series


def makeFraction(series):
    n = series[-1][0]
    d = series[-1][1]
    for pair in series[len(series) - 2 :: -1]:
        n, d = d * pair[0], pair[1] * d + n

    return 2 * d + n, d


def makeFraction2(series):
    n = 0
    d = 0
    for pair in series[::-1]:
        if not n:
            n = pair[0]
            d = pair[1]
        else:
            n, d = d * pair[0], pair[1] * d + n

    return 2 * d + n, d


e = makeFraction(eFractions(100))
x = str(e[0])

total = 0
for c in x:
    total += int(c)

print(total)
