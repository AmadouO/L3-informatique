const my_objet = {
    x : 0,
    y : 0,
    do(){
        console.log( this.x , this.y);
    }
};

my_objet.x = 5;
my_objet.y = 6;
my_objet.do();