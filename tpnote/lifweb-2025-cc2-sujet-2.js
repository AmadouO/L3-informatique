/*
    LIFWEB 2025 -- CC2 TP noté
    SUJET 2 - 11:45

    Compléter les exercices demandés en 60 minutes (hors tiers-temps).
    Déposer dans la cellule correspondante de Tomuss le fichier JS complété et UNIQUEMENT ce fichier.

    Rendu attendu : https://tabard.fr/dd/lifweb-CC2-2-2025.mov
    Les exercices 1 à 3 se suivent, le 4 est indépendant

    Les rendus par mail ne seront PAS pris en compte (sauf tiers-temps).
    Un fichier qui ne se charge pas correctement ne sera PAS pris en compte.

    Tous les documents et l'accès à internet sont autorisés : votre code, les corrections, MDN, stack-overflow, etc.
    Vous pouvez utiliser votre ordinateur personnel ou les ordinateurs de la salle de TP.

    Toute communication entre humains est INTERDITE.
    Les IAs/LLMs (ChatGPT, GitHub Copilot, etc.) sont INTERDITS.
    Si vous utilisez Copilot ou un outil similaire dans votre IDE, DÉSACTIVEZ-LE.

    Le barême est donné à titre indicatif et pourra être adapté en cas de déséquilibre entre les groupes.
    
    */

// Exercice 1
//
// Compléter la fonction afficherAppartements() cette fonction prend en entrée
// une liste d'appartement et les affiche.
//
// Au chargement de la page, la fonction est appelée avec la liste d'appartement
// fournie dans le fichier lifweb-2025-cc2-sujet-2-data.js
//
// TODO Parcourir la liste d'appartements et pour chaque appartement :
// 1. Créer un div ayant pour nom de classe "appartement", et
//    un id correspondant à celui de l'appartement dans le jeu de données. (1pt)
// 2. Dans ce div ajouter un titre h3 présentant l'appartement ainsi
//    que des paragraphes pour l'adresse, le loyer et les charges, la surface (1pt)
// 3. Dans ce div ajouter aussi le nombre de colocataires. (1pt)
// 4. Dans ce div ajouter un bouton "Voir les colocataires"
//    donner une classe à ce bouton elle sera utilisée dans l'exo 2 (0,5pt)
// 5. Insérer ce div dans la page Web à l'endroit prévu pour cela (0,5pt)
//
// Favoriser les bonnes pratiques vues en cours que ce soit sur les boucles,
// La manipulation du DOM, ou la manipulation de tableau javascript.

const appartement = data.appartements
console.log("appartement");

function afficherAppartements(listeAppartements) {
  // TODO
  const div_listeAppartements = document.querySelector("#listeAppartements");
 

  appartement.forEach(element => {
    const div_appart = document.createElement('div');
    div_appart.classList.add('appartement');
    div_appart.id = element.id;

    const titre = document.createElement('h3');
    titre.textContent = element.titre;

    const address = document.createElement('p');
    address.textContent = element.adresse

    const loyer = document.createElement('p');
    loyer.textContent = element.loyer;

    const charge = document.createElement('p');
    charge.textContent = element.charges;

    const surface = document.createElement('p');
    surface.textContent = element.surface;

    const colocataire = document.createElement('p')
    colocataire.textContent = element.colocatairesID;

    const btn_voir_coloc = document.createElement('button');
    btn_voir_coloc.textContent = "voir_coloc"
    btn_voir_coloc.classList.add('voir_coloc');
    
  
    div_appart.appendChild(titre);
    div_appart.appendChild(address);
    div_appart.appendChild(loyer);
    div_appart.appendChild(charge);
    div_appart.appendChild(surface);
    div_appart.appendChild(colocataire);
    div_appart.appendChild(btn_voir_coloc);

    div_listeAppartements.appendChild(div_appart);

  });


  exo2(); // garder cet appel
}

console.log(afficherAppartements(data.appartements));

// Exercice 2 (4pt)
//
// Compléter la fonction exo2() qui va ajouter à tous les boutons
// "Voir les colocataires" un event listener (1pt)
// pour qu'en cas de click :
//
// 1. On retire la classe "selected" de tous les div présentant un appartement (1pt)
// 2. On ajoute la classe "selected" au div contenant le bouton sur lequel
//    on vient de cliquer (1pt)
// 3. On appelle afficherColocataires(id), cet id correspond à l'appartement
//    dont on veut afficher les colocataires. (1pt)
//
function exo2() {}

// Exercice 3 - Affichage des colocataires (7pt)
//
// 1. A partir de appartID retrouver l'appartement auquel il est fait référence (1pt)
//
// Une fois l'appartement retrouvé, appartement.colocataireId fournit
// un tableau des identifiants des colocataires
//
// Pour chaque colocataire de l'appartement :
// 2. reconstruire un url à requêter de la forme (1pt) :
//    http://lifweb.pages.univ-lyon1.fr/CC2/colocataires/colocataire-1.json
//    colocataire-1 correspondant au colocataire d'id==1
// 3. requêter cette url en utilisant fetch() et then(). (2pt)
// 4. si la requête fonctionne construire un div (1pt)
//    - avec pour classe "colocataire" et id l'id du colocataire
//    - Le nom / prénom du colocataire en h3
//    - un paragraphe pour l'age, les études, le contact, les hobbies
// 5. En cas d'erreur afficher un div signalant un problème (1pt)
//
// 6. Si vous testez plusieurs appartements de suite,
//    les colocataires vont s'ajouter dans le div au fur et à mesure.
//    Au tout début de la fonction effacer le contenu du div pour
//    que seul s'affiche les colocataires de l'appartement sélectionné (1pt)
function afficherColocataires(appartID) {
  // Afficher les colocataires de l'appartement sélectionné
}

// Exercice 4 - Calcul et affichage des statistiques (5pt)
//
// En utilisant au maximum les array methods https://javascript.info/array-methods,
// notamment reduce, calculer les statistiques suivantes des appartements :
// - prix moyen (2pt si pas de boucle, 1pt si boucle). Le prix moyen doit prendre en compte le loyer et les charges (+1pt si les deux sont pris en compte dans le calcul)
// - surfaceMoyenne (2pt si pas de boucle, 1pt si boucle)
//
function calculerStatistiques() {
  // Calculer le prix moyen (loyer + charges)
  // Calculer la surface moyenne
  // Afficher les statistiques
}

calculerStatistiques();
