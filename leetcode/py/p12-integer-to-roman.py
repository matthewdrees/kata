class Solution:
    def intToRoman(self, num: int) -> str:
        r = []

        # Thousands
        if num >= 2000:
            if num >= 3000:
                r.append("MMM")
                num -= 3000
            else:
                r.append("MM")
                num -= 2000
        elif num >= 1000:
            r.append("M")
            num -= 1000

        # Hundreds
        if num >= 400:
            if num >= 600:
                if num >= 800:
                    if num >= 900:
                        r.append("CM")
                        num -= 900
                    else:
                        r.append("DCCC")
                        num -= 800
                elif num >= 700:
                    r.append("DCC")
                    num -= 700
                else:
                    r.append("DC")
                    num -= 600
            else:
                if num >= 500:
                    r.append("D")
                    num -= 500
                else:
                    r.append("CD")
                    num -= 400
        else:
            if num >= 200:
                if num >= 300:
                    r.append("CCC")
                    num -= 300
                else:
                    r.append("CC")
                    num -= 200
            else:
                if num >= 100:
                    r.append("C")
                    num -= 100

        # Tens
        if num >= 40:
            if num >= 60:
                if num >= 80:
                    if num >= 90:
                        r.append("XC")
                        num -= 90
                    else:
                        r.append("LXXX")
                        num -= 80
                elif num >= 70:
                    r.append("LXX")
                    num -= 70
                else:
                    r.append("LX")
                    num -= 60
            else:
                if num >= 50:
                    r.append("L")
                    num -= 50
                else:
                    r.append("XL")
                    num -= 40
        else:
            if num >= 20:
                if num >= 30:
                    r.append("XXX")
                    num -= 30
                else:
                    r.append("XX")
                    num -= 20
            else:
                if num >= 10:
                    r.append("X")
                    num -= 10

        # Ones
        if num >= 4:
            if num >= 6:
                if num >= 8:
                    if num >= 9:
                        r.append("IX")
                        num -= 9
                    else:
                        r.append("VIII")
                        num -= 8
                elif num >= 7:
                    r.append("VII")
                    num -= 7
                else:
                    r.append("VI")
                    num -= 6
            else:
                if num >= 5:
                    r.append("V")
                    num -= 5
                else:
                    r.append("IV")
                    num -= 4
        else:
            if num >= 2:
                if num >= 3:
                    r.append("III")
                    num -= 3
                else:
                    r.append("II")
                    num -= 2
            else:
                if num >= 1:
                    r.append("I")
                    num -= 1

        return "".join(r)


if __name__ == "__main__":

    s = Solution()
    tests = (
        (1, "I"),
        (2, "II"),
        (3, "III"),
        (4, "IV"),
        (5, "V"),
        (6, "VI"),
        (7, "VII"),
        (8, "VIII"),
        (9, "IX"),
        (10, "X"),
        (40, "XL"),
        (50, "L"),
        (58, "LVIII"),
        (90, "XC"),
        (91, "XCI"),
        (94, "XCIV"),
        (99, "XCIX"),
        (100, "C"),
        (400, "CD"),
        (500, "D"),
        (900, "CM"),
        (1000, "M"),
        (1994, "MCMXCIV"),
        (3999, "MMMCMXCIX"),
    )

    for test in tests:

        num = test[0]
        exp = test[1]
        ans = s.intToRoman(num)
        if exp != ans:
            print(f"FAIL. num: {num}, exp: {exp}, ans: {ans}")
