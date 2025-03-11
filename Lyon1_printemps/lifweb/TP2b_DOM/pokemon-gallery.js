/* === Partie 1: Gestion des événements et manipulation du DOM === */
// TODO: Ajoutez un événement 'change' sur le select#deck-choice
// L'événement doit :
// 1. Récupérer la valeur sélectionnée
// 2. Mettre à jour le titre du deck dans #deck-title

function initDeckSelector(){
  const deck_choice = document.querySelector('select#deck-choice');
  deck_choice.addEventListener('change', () =>{
    const deck_title = document.querySelector('#deck-title');
    let deck_id = deck_choice.value;

    let deck_name = decks[deck_id].nom; // Recuperer le nom du deck selectionné
    deck_title.textContent = deck_name; // Mettre à jour le titre du deck dans #deck-title

    afficherGalerie(deck_id);
  });
}


/* === Partie 2: Affichage de la galerie === */
// TODO: Créez une fonction qui affiche les pokémons du deck sélectionné
// Pour chaque pokémon, créez une card avec :
// - L'image du pokémon
// - Son nom
// - Son type
function afficherGalerie(deckId) {
  // Votre code ici
  const div_affiche_gallery = document.querySelector('#gallery');
  div_affiche_gallery.textContent = ""; // Vider la galerie

  if ( !decks[deckId]){ // Verifier si le deck existe
    console.error("Deck introuvable ");
    return;
  }

  const pokemons = decks[deckId]["pokemons"]; //Recuperer les pokemons du deck selectionné 

  pokemons.forEach(pokemon => {
    //Creation de la carte de pokemons
    const carte = document.createElement("div");
    carte.classList.add("pokemon-card");

    //Creation de l'image de pokemons
    const img = document.createElement("img");
    img.src = pokemon.image;
    img.alt = pokemon.nom;

    //Creation du nom de pokemons
    const nom_pok = document.createElement("h3");
    nom_pok.textContent = pokemon.nom;

    //Creation du type de pokemons
    const type_pok = document.createElement("p");
    type_pok.textContent = pokemon.type;

    carte.appendChild(nom_pok);
    carte.appendChild(type_pok);
    carte.appendChild(img);


  div_affiche_gallery.appendChild(carte);   
  });

  update_select(1);

}
/* === Partie 3: Navigation clavier === */
// TODO: Ajoutez un listener d'événements pour les touches:
// - Flèche gauche: reculer dans la liste
// - Flèche droite: avancer dans la liste
function update_select(selected_index) {
  const gallery = document.getElementById("gallery");

  // Vérifiez si la galerie existe
  if (!gallery) {
    console.error("La galerie n'a pas été trouvée.");
    return;
  }

  const carte = Array.from(gallery.children);
  if (carte.length === 0) {
    return;
  }

  // Retirer la sélection précédente
  carte.forEach(cart => {
    cart.classList.remove("selected");
  });

  // Appliquer la sélection à la carte actuelle
  if (carte[selected_index]) {
    carte[selected_index].classList.add("selected");
  }
}

function initNavigation() {
  let selected_index = 0;

  document.addEventListener('keydown', (event) => {
    const gallery = document.getElementById("gallery");

    // Vérifiez si la galerie existe
    if (!gallery) {
      console.error("La galerie n'a pas été trouvée.");
      return;
    }

    const carte = Array.from(gallery.children);
    if (carte.length === 0) {
      return;
    }

    if (event.key == "ArrowRight") {
      selected_index = (selected_index + 1) % carte.length; // Carte Suivante
      console.log("Flèche droite :", selected_index);
    } else if (event.key === "ArrowLeft") {
      selected_index = (selected_index - 1 + carte.length) % carte.length; // Carte Précédente
      console.log("Flèche gauche :", selected_index);
    }

    update_select(selected_index);
  });

  update_select(selected_index);
}


// Initialisation
document.addEventListener("DOMContentLoaded", () => {
  initDeckSelector();
  initNavigation();
});
