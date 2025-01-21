const my_object = {
    x: 0, // valeur initiale de x
    y: 0, // valeur initiale de y
    do() {
        console.log(`x: ${this.x}, y: ${this.y}`);
    }
};

// Exemple d'utilisation :
my_object.x = 10;
my_object.y = 20;
my_object.do(); // Affiche "x: 10, y: 20"
