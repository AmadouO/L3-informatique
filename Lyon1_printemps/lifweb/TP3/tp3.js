//document.addEventListener("DOMContentLoaded", () => {
  const quote = document.querySelector("q");
  const input = document.querySelector("input[name='size-selector']");
  const addButton = document.querySelector("#add_button");
  const buttonContainer = document.querySelector("#div_add_button");

  addButton.addEventListener("click", () => {
    const size = input.value; // Capture la valeur actuelle de l'input
    const newButton = document.createElement("button");
    newButton.textContent = `Taille ${size}px`;
    
    // Utilisation d'une fermeture pour lier la taille au moment de la création
    newButton.addEventListener("click", () => {
      quote.style.fontSize = `${size}px`;
    });
    
    buttonContainer.appendChild(newButton);
  });
//});

const database = [
  { name: "Alice", age: 40, sal: 2500 },
  { name: "Bob", age: 17, sal: -1 },
  { name: "Charlie", age: 30, sal: 1800 },
  { name: "Denise", age: 12, sal: -1 },
];

function persn_majeur_salair_sup(data){
  return data.filter(elem => elem.age > 18).every(elem => elem.sal > 1500);
  
  /*let adulte = true;
  data.forEach(element => {
      if(element.age >= 18 && element.sal <= 1500){
        adulte = false;
      }  
  });
  return adulte;
  for(let i = 0; i < data.length; i++){
    //const elem = data[i];
    if(data[i].age >= 18 && data[i].sal <= 1500){
      return false;
    }
  }
  return true;*/
}
console.log("Exist - il une Personne majeur dont le salaire est superieur a 1500 : " + persn_majeur_salair_sup(database));

//************************************************************************************** */

/*
function nom_age_perso_majeur(data){
    let perso_majeur = data.filter(elem => elem.age >= 18);
    let forme_nom_age = perso_majeur.map(elem => `${elem.name} : ${elem.age}`);
   // console.log(perso_majeur)
   // console.log(forme_nom_age);
    return forme_nom_age;
}*/

function nom_age_perso_majeur(data){
  let forme_nom_age = [];
  for(let i = 0; i < data.length; i++){
    if(data[i].age >= 18){
      forme_nom_age.push(`${data[i].name} : ${data[i].age}`);
    }
  }
  return forme_nom_age;
}

console.log("Nom et age des personne majeur : " + nom_age_perso_majeur(database));
//**************************************************************************************** */
function salair_moyen_perso_maj(data){
  const {somme_salaire, nbr_majeur} = data.reduce(
    (acc, elem) =>{

      if(elem.age >= 18){

       acc.somme_salaire += elem.sal; //  acc.somme_salaire = acc.somme_salaire + elem.sal
        acc.nbr_majeur++ ; // nombre de majeurs

      }
      return acc;

    }, { somme_salaire : 0, nbr_majeur :0}
  );

  if(nbr_majeur > 0){
    return somme_salaire / nbr_majeur
  }else{
    return 0;
  } 
}

console.log("salaire moyen des personne majeur "+ salair_moyen_perso_maj(database));

//**************************************************************************** */

function ecart_type_salaire_perso_majeur(data){
  const {somme_salaire, somme_carre, nbr_majeur} = data.reduce(
    (acc, elem) => {
      if (elem.age >= 18){
        acc.somme_salaire += elem.sal;  // somme des salaires des majeurs
        acc.somme_carre += elem.sal ** 2; // somme des carrés des salaires des majeurs (elem.sal ** 2) est equivalent à elem.sal * elem.sal
        acc.nbr_majeur++;
      }

      //console.log(acc);

      return acc; // retourner l'accumulateur

    }, { somme_salaire : 0, somme_carre : 0, nbr_majeur : 0} // initialisation des valeurs de l'accumulateur
  );

  if(nbr_majeur === 0 ){
    return 0; //eviter la division par 0
  }

  const moyenne_salaire = somme_salaire / nbr_majeur; // moyenne des salaires des majeurs
  const moyenne_carre = somme_carre / nbr_majeur; // moyenne des carrés des salaires des majeurs

  const ecart_type = Math.sqrt(moyenne_carre - moyenne_salaire ** 2); // ecart type des salaires des majeurs

  return ecart_type;
}

console.log("Ecart type de salaire des personnes majeurs : " + ecart_type_salaire_perso_majeur(database));




// decorateur pour afficher le temps d'execution d'une fonction
function chrono(fct) {
  // c.f. https://javascript.info/rest-parameters-spread
  return function (...args) { // args est un tableau contenant les arguments de la fonction
    const start = Date.now(); // Enregistre le temps de début
    // const result = fct(...args);
    const result = fct.call(this, ...args); // execute la fonction fct 
    const end = Date.now(); // Enregistre le temps de fin
    console.info(`${fct.name}(...) executed in ${end - start}ms`); // Affiche le temps d'exécution
    return result;
  };
}

// Exemple d'utilisation du décorateur chrono sur la fonction sum
function sum(array) {
  return array.reduce((a, b) => a + b, 0);
}

// pas d'équivalent de range() Python en JS
// le hack suivant permet de créer un tableau [0, 1, ..., 1e7 - 1]
const test = [...Array.from({ length: 1e7 }).keys()]; // tableau de 10^7 éléments

console.log(sum(test));
const sumChrono = chrono(sum);
console.log(sumChrono(test));
setTimeout(() => sumChrono(test), 1000);

/**
 * Fonctions utilisables pour tester les décorateurs de l'exo 4
 */
function add(a, b) {
  return a + b;
}

function sayHello(name) {
  if (name != undefined) return "Hello " + name;
  return undefined;
}
