const pokemons = [
    { nom: "Pikachu", type: "électrique", niveau: 15 },
    { nom: "Salamèche", type: "feu", niveau: 12 },
    { nom: "Carapuce", type: "eau", niveau: 14 },
    { nom: "Bulbizarre", type: "plante", niveau: 13 },
    { nom: "Roucool", type: "normal/vol", niveau: 10 }
];

//console.log(pokemons);

function finde(poke){
    return poke.find(elem => elem.nom  == "Roucool"); 
}
function findindexo(poke){
    return poke.findIndex(elem => elem.nom == "Bulbizarre" ) 
}

function findlasto(poke){
    return poke.findLast(elem => elem.niveau >= 14)
}

function equipeElite(poke){
    return poke.filter(ele => ele.niveau > 12);
}

function presentationEquipe(poke){
    //Quand transformer un tableau : Si tu veux appliquer une opération (comme un calcul ou un formatage) à chaque élément et obtenir un nouveau tableau.
    return poke.map(elem => 
        elem.nom.concat(" (type : ", elem.type, ") - Niveau ", elem.niveau)).join("\n");
}
console.log(finde(pokemons));
console.log();
console.log(findindexo(pokemons));
console.log();
console.log(findlasto(pokemons));
console.log();
console.log(equipeElite(pokemons));
console.log();
console.log(presentationEquipe(pokemons));


