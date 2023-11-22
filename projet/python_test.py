def parenthesize(word_length):
    def generate_parentheses(current, left, right):
        if len(current) == 2 * word_length:
            print(current)
            return
        if left < word_length:
            generate_parentheses(current + '(', left + 1, right)
        if right < left:
            generate_parentheses(current + ')', left, right + 1)

    generate_parentheses('', 0, 0)

# Exemple d'utilisation avec un mot de longueur 3
mot_longueur = 10
parenthesize(mot_longueur)
