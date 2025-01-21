function iterate_array_forof(arr) {
  console.log("for...of");
  // À compléter...
}

function iterate_array_forin(arr) {
  console.log("for...in");
  // À compléter...
}

function iterate_array_for(arr) {
  console.log("for");
  // À compléter...
}

function iterate_array_while(arr) {
  console.log("while");
  // À compléter...
}

function iterate_array_foreach(arr) {
  console.log("forEach");
  // À compléter...
}

function test() {
  // remplacer iterate_array par la fonction que vous souhaitez tester
  iterate_array([1, 2, 3, 6, 5, 4]);
  iterate_array([
    { a: 0, b: 1 },
    { a: 1, b: 42 },
  ]);
}
/**
 * 
 * 
 * function iterate_array_forof(arr) {
  console.log("for...of");
  for (const element of arr) {
    console.log(element);
  }
}

function iterate_array_forin(arr) {
  console.log("for...in");
  for (const index in arr) {
    console.log(`Index: ${index}, Value: ${arr[index]}`);
  }
}

function iterate_array_for(arr) {
  console.log("for");
  for (let i = 0; i < arr.length; i++) {
    console.log(`Index: ${i}, Value: ${arr[i]}`);
  }
}

function iterate_array_while(arr) {
  console.log("while");
  let i = 0;
  while (i < arr.length) {
    console.log(`Index: ${i}, Value: ${arr[i]}`);
    i++;
  }
}

function iterate_array_foreach(arr) {
  console.log("forEach");
  arr.forEach((element, index) => {
    console.log(`Index: ${index}, Value: ${element}`);
  });
}

function test() {
  const testArrays = [
    [1, 2, 3, 6, 5, 4],
    [
      { a: 0, b: 1 },
      { a: 1, b: 42 },
    ],
  ];

  for (const iterate_array of [
    iterate_array_forof,
    iterate_array_forin,
    iterate_array_for,
    iterate_array_while,
    iterate_array_foreach,
  ]) {
    console.log(`\nTesting ${iterate_array.name}:\n`);
    for (const arr of testArrays) {
      iterate_array(arr);
    }
  }
}
*********************************************


function equipeElite(pokemonArray) {
  return pokemonArray.filter((pokemon) => pokemon.level > 12);
}

// Test de la fonction
const eliteTeam = equipeElite(pokemons);
console.log("Équipe d'élite (niveau > 12) :");
console.log(eliteTeam);
**********************************************

function presentationEquipe(pokemonArray) {
  return pokemonArray
    .map(
      (pokemon) =>
        `${pokemon.name} (Type: ${pokemon.type}) - Niveau ${pokemon.level}`
    )
    .join("\n");
}

// Test de la fonction
console.log("Présentation de l'équipe :");
console.log(presentationEquipe(eliteTeam));
**********************************************

function analyseEquipe(pokemonArray) {
  const typeCount = {};

  pokemonArray.forEach((pokemon) => {
    // Découper les types en cas de double type
    const types = pokemon.type.split("/");
    types.forEach((type) => {
      if (typeCount[type]) {
        typeCount[type]++;
      } else {
        typeCount[type] = 1;
      }
    });
  });

  return typeCount;
}

// Test de la fonction
const teamAnalysis = analyseEquipe(eliteTeam);
console.log("Analyse de l'équipe :");
console.log(teamAnalysis);

**********************************************

// Filtrer les Pokémon avec un niveau supérieur à 30
const highLevelTeam = equipeElite(pokemons.filter((pokemon) => pokemon.level > 30));

// Présentation de l'équipe
console.log("Présentation de l'équipe (niveau > 30) :");
console.log(presentationEquipe(highLevelTeam));

// Analyse de l'équipe
console.log("Analyse de l'équipe (niveau > 30) :");
console.log(analyseEquipe(highLevelTeam));
**********************************************
 */