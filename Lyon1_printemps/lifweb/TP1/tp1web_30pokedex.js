const pokemons = [
    { nom: "Pikachu", type: "électrique", niveau: 15 },
    { nom: "Salamèche", type: "feu", niveau: 12 },
    { nom: "Carapuce", type: "eau", niveau: 14 },
    { nom: "Bulbizarre", type: "plante", niveau: 13 },
    { nom: "Roucool", type: "normal/vol", niveau: 10 }
];

//console.log(pokemons);

function equipeElite(poke){
    return poke.filter(ele => ele.niveau > 13);
}

console.log(equipeElite(pokemons));