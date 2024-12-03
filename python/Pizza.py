class Pizza:
    def __init__(self, base, prix, diametre , style, ingredient):
        self.base = base
        self.prix = prix
        self.diametre = diametre
        self.style = style
        self.ingredient = ingredient
    
    def ajout_ingredients(self, nouvel_ingredient):
        if nouvel_ingredient == "ananas":
            raise TypeError("les ananas ne vont pas sur les pizzas ")
        self.ingredient.append(nouvel_ingredient)
        self.prix = self.prix + 1

    
    def servir(self,table):
        print("j'amene la pizza a la table ", table)

    def livre(self, addresse):
        print("je livre la pizza a l'addresse : ", addresse)

base = input("quelle base voulez-vous ? (tomate/creme) :")
taille = input("quelle taille voulez-vous ? (moyenne / grande) : ")
style = input("quel taille voulez-vous ? (classique, calzone) :")
ingredient = input("quels ingredients voulez-vous ? : ")

diametre = 30
if taille == 'grande':
    diametre = 34

ingredient = ingredient.split(', ')

prix = 5 + len(ingredient)

pizza = Pizza(
    base = base,
    diametre = diametre,
    style = style,
    ingredient = ingredient,
    prix = prix
)

print(pizza.ingredient, pizza.prix)
pizza.ajout_ingredients("olive")
print(pizza.ingredient, pizza.prix)
pizza.livre("14 rue du docteur crestin ")
pizza.servir(13)
ananas = input("voulez-vous ajouter des ananas ? (oui, non )")

if ananas == "oui":
    pizza.ajout_ingredients("ananas")