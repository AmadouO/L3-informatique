/* === Partie 1: Gestion des événements et manipulation du DOM === */
// TODO: Ajoutez un événement 'change' sur le select#deck-choice
// L'événement doit :
// 1. Récupérer la valeur sélectionnée
// 2. Mettre à jour le titre du deck dans #deck-title
function initDeckSelector() {
  // Votre code ici
  const deck_choice = document.querySelector('select#deck-choice');
  deck_choice.addEventListener('change', () =>{
  const deck_title = document.querySelector('#deck-title');
  const deck_choice_value = deck_choice.value;
  //console.log(deck_choice) 
  //onsole.log(deck_title)
  console.log(deck_choice_value)

  const deck_name = decks[deck_choice_value]['nom'];
  console.log(deck_name);
  deck_title.textContent = deck_name;

  afficherGalerie(deck_choice_value);

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
  const div_pokemon_gallery = document.querySelector('#gallery');
  div_pokemon_gallery.textContent = "";

  const pokemons = decks[deckId]['pokemons'];

  pokemons.forEach(pokemon => {
    const card = document.createElement('div');
    card.classList.add('pokemon-card');
    
    const img = document.createElement('img');
    img.src = pokemon.image;
    img.alt = pokemon.nom;

    const nom = document.createElement('h3');
    nom.textContent = pokemon.nom;


    const type = document.createElement('p');
    type.textContent = pokemon.type;


    card.appendChild(nom);
    card.appendChild(type);
    card.appendChild(img);

  div_pokemon_gallery.appendChild(card);

  });
  update_selected(0)
}

/* === Partie 3: Navigation clavier === */
// TODO: Ajoutez un listener d'événements pour les touches:
// - Flèche gauche: reculer dans la liste
// - Flèche droite: avancer dans la liste
function update_selected(index){
  const gallery = document.querySelector("#gallery"); //

  const cards = Array.from(gallery.children); // on récupère les enfants de gallery et on les met dans un tableau
  console.log(gallery, cards)

  cards.forEach((_, ind) =>{ 
    if(ind === index){ 
      cards[ind].classList.add("selected");
    } else {
      cards[ind].classList.remove("selected");
    }
  });

  //cards[index].classList.remove("selected") //
  //cards[index].classList.add("selected"); //
}
function initNavigation() {
  // Votre code ici
  const gallery = document.querySelector("#gallery");
  let selected_index = 0;

  document.addEventListener('keydown', (event) => {
    const cards = Array.from(gallery.children);

    if(event.key == "ArrowRight"){

      selected_index = (selected_index + 1) % cards.length;

    }else if(event.key == "ArrowLeft"){

      selected_index = (selected_index - 1 + cards.length) % cards.length;

    }
    update_selected(selected_index);
  });
  update_selected(selected_index);
}

// Initialisation
document.addEventListener("DOMContentLoaded", () => {
  initDeckSelector();
  initNavigation();
});
