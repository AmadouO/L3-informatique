/* === Partie 1: Gestion des événements et manipulation du DOM === */
// TODO: Ajoutez un événement 'change' sur le select#deck-choice
// L'événement doit :
// 1. Récupérer la valeur sélectionnée
// 2. Mettre à jour le titre du deck dans #deck-title


function initDeckSelector() {
const deck_choice = document.querySelector('select#deck-choice');

  // Votre code ici
  deck_choice.addEventListener('change', change_title)
}

let change_title = function(){
const deck_title = document.querySelector('#deck-title');
//const deck_choice = document.querySelector('select#deck-choice');


  let dec_id = document.querySelector("#deck-choice").value;
  let deckName = decks[dec_id]["nom"];

  deck_title.innerText= deckName;
}

/* === Partie 2: Affichage de la galerie === */
// TODO: Créez une fonction qui affiche les pokémons du deck sélectionné
// Pour chaque pokémon, créez une card avec :
// - L'image du pokémon
// - Son nom
// - Son type
function afficherGalerie(deckId) {
  // Votre code ici
}

/* === Partie 3: Navigation clavier === */
// TODO: Ajoutez un listener d'événements pour les touches:
// - Flèche gauche: reculer dans la liste
// - Flèche droite: avancer dans la liste
function initNavigation() {
  // Votre code ici
}

// Initialisation
document.addEventListener("DOMContentLoaded", () => {
  initDeckSelector();
  initNavigation();
});
