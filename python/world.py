mot_mystere = 'python'
mot_public = '_' * len(mot_mystere)
nb_vie = 7

while nb_vie > 0 and mot_mystere != mot_public:
    myst = input('Donner une lettre :')
    if myst in mot_mystere:
        for i in range(len(mot_mystere)):
            if mot_mystere[i] == myst:
                mot_public = mot_public[:i] + myst +mot_public[i + 1:]
    else:
        nb_vie -= 1

    if mot_public == mot_mystere:
        print(mot_mystere)
    elif nb_vie == 0:
        print("perdu")
    else:
        print("il vous reste :", nb_vie)
        print("le mot est :", mot_public)
