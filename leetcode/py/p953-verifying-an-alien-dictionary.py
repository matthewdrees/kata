# LeetCode 953. Verifying an Alien Dictionary.
from typing import List
import pyperf


class Solution:
    def isAlienSorted(self, words: List[str], order: str) -> bool:
        d = {}
        for x, c in enumerate(order):
            d[c] = x
        for x in range(0, len(words) - 1):
            w1 = words[x]
            w2 = words[x + 1]
            len_w1 = len(w1)
            len_w2 = len(w2)
            y = 0
            while True:
                if y < len_w1:
                    if y < len_w2:
                        if w1[y] != w2[y]:
                            if d[w1[y]] < d[w2[y]]:
                                break
                            else:
                                return False
                    else:
                        return False
                else:
                    break
                y += 1
        return True


if __name__ == "__main__":
    s = Solution()
    tests = (
        (["hello", "leetcode"], "hlabcdefgijkmnopqrstuvwxyz", True),
        (["word", "world", "row"], "worldabcefghijkmnpqstuvxyz", False),
        (["apple", "app"], "abcdefghijklmnopqrstuvwxyz", False),
        (["hello", "hello"], "abcdefghijklmnopqrstuvwxyz", True),
    )
    for test in tests:
        words = test[0]
        order = test[1]
        exp = test[2]
        ans = s.isAlienSorted(words, order)
        if exp != ans:
            print(f"FAIL. words: {words}, order: {order}, exp: {exp}, ans: {ans}")

    perf_words = [
        "abdominohysterectomy",
        "acetylcholinesterase",
        "acetylmethylcarbinol",
        "adrenocorticosteroid",
        "adrenocorticotrophic",
        "adrenocorticotrophin",
        "anarchoindividualist",
        "anatomicochirurgical",
        "anatomicophysiologic",
        "anitinstitutionalism",
        "anopisthographically",
        "anthrohopobiological",
        "anthropogeographical",
        "anthropomorphisation",
        "anthropomorphization",
        "anthropomorphotheist",
        "anthropophysiography",
        "anthropoteleological",
        "antianthropomorphism",
        "antiaristocratically",
        "antiauthoritarianism",
        "anticapitalistically",
        "anticonfederationism",
        "anticonfederationist",
        "anticonservativeness",
        "anticonstitutionally",
        "antiecclesiastically",
        "antienthusiastically",
        "antienvironmentalism",
        "antienvironmentalist",
        "antiinstitutionalist",
        "antiinsurrectionally",
        "antiinsurrectionists",
        "antimilitaristically",
        "antiparliamentarians",
        "antiprestidigitation",
        "antitintinnabularian",
        "archaeopterygiformes",
        "arteriosympathectomy",
        "autodepolymerization",
        "ballistocardiography",
        "barothermohygrograph",
        "benzofuroquinoxaline",
        "biblicopsychological",
        "blepharochromidrosis",
        "blepharohematidrosis",
        "bronchoaspergillosis",
        "bronchoesophagoscopy",
        "calcareoargillaceous",
        "characteristicalness",
        "chemicomineralogical",
        "chemicophysiological",
        "chemoautotrophically",
        "chemotherapeutically",
        "chemotherapeuticness",
        "chlamydobacteriaceae",
        "cholecystenterostomy",
        "cholecystgastrostomy",
        "cholecystnephrostomy",
        "chronocinematography",
        "cinephotomicrography",
        "compartmentalization",
        "consubstantiationist",
        "counterdemonstration",
        "counterdemonstrators",
        "counterdisengagement",
        "counterestablishment",
        "counterexpostulation",
        "counterrevolutionary",
        "counterrevolutionist",
        "counterrevolutionize",
        "crystallographically",
        "decahydronaphthalene",
        "desoxycorticosterone",
        "dimethylanthranilate",
        "diphenylchloroarsine",
        "diphenylquinomethane",
        "disdenominationalize",
        "disestablismentarian",
        "disproportionateness",
        "duodenojejunostomies",
        "electroballistically",
        "electrocardiographic",
        "electrocauterization",
        "electrochronographic",
        "electrocontractility",
        "electroencephalogram",
        "electrogalvanization",
        "electrohydraulically",
        "electrometallurgical",
        "electrophysiological",
        "electropneumatically",
        "electroretinographic",
        "electrosynthetically",
        "electrotherapeutical",
        "encephalographically",
        "encephalomeningocele",
        "encephalomyocarditis",
        "epididymodeferential",
        "establismentarianism",
    ]
    runner = pyperf.Runner()
    runner.bench_func("f", s.isAlienSorted, perf_words, "abcdefghijklmnopqrstuvwxyz")