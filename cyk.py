def cyk_algorithm(word, grammar):
    n = len(word)
    table = [[set() for _ in range(n)] for _ in range(n)]

    # 1. lépés: Inicializálás
    for i in range(n):
        for lhs, rhs in grammar:
            if rhs == word[i]:
                table[i][i].add(lhs)

    # 2. lépés: Rekurzív kitöltés
    for length in range(2, n+1):  # hosszúság 2-től n-ig
        for start in range(n-length+1):
            end = start + length - 1
            for mid in range(start, end):
                for lhs, rhs in grammar:
                    if len(rhs) == 2:
                        if rhs[0] in table[start][mid] and rhs[1] in table[mid+1][end]:
                            table[start][end].add(lhs)

    # 3. lépés: Ellenőrzés
    start_symbol = 'S'  # kezdő szimbólum, pl. 'S'
    return start_symbol in table[0][n-1]

# Példa grammatikai szabályok (három szabály)
grammar = [
    ('S', 'AB'),
    ('A', 'a'),
    ('B', 'b')
]

word = "ab"
if cyk_algorithm(word, grammar):
    print(f"A szó '{word}' érvényes.")
else:
    print(f"A szó '{word}' nem érvényes.")
