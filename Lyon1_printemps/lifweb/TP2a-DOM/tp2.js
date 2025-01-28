"use strict";
console.info("app.js loading...");

console.info("...app.js loaded");

const count = 0;

const incrementBtn = document.querySelector("#incrementBtn");
const counter = document.querySelector("#counter");
const decrementBtn = document.querySelector("#decrementBtn");

// Fonction pour mettre à jour l'affichage du compteur
function updateCounter() {
    counter.textContent = count;
  }
  
  // Handler pour le bouton -
  decrementBtn.addEventListener("click", () => {
    count--;
    updateCounter();
  });
  
  // Handler pour le bouton +
  incrementBtn.addEventListener("click", () => {
    count++;
    updateCounter();
  });
  
  // Créer le bouton reset
  const resetBtn = document.createElement("button");
  resetBtn.textContent = "reset";
  
  // Ajouter le bouton reset à droite du bouton +
  incrementBtn.after(resetBtn);
  
  // Handler pour le bouton reset
  resetBtn.addEventListener("click", () => {
    count = 0;
    updateCounter();
  });

  "use strict";

// Récupérer les éléments du DOM *******************************************************************2
const emailInput = document.getElementById("emailInput");
const validateBtn = document.getElementById("validate-btn");
const errorMessage = document.getElementById("errorMessage");

// Regex pour valider le format de l'email
const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;

// Fonction pour valider l'email
function validateEmail() {
  const email = emailInput.value;

  if (emailRegex.test(email)) {
    // Email correctement formaté
    emailInput.style.backgroundColor = "lightgreen";
    errorMessage.textContent = ""; // Effacer le message d'erreur
  } else {
    // Email mal formaté
    emailInput.style.backgroundColor = "lightcoral";
    errorMessage.textContent = "L'email n'est pas valide.";
  }
}

// Écouteur d'événement pour le clic sur le bouton Valider
validateBtn.addEventListener("click", (event) => {
  event.preventDefault(); // Empêcher le rechargement de la page (si le formulaire est soumis)
  validateEmail();
});

// Écouteur d'événement pour les modifications du champ d'input
emailInput.addEventListener("input", () => {
  validateEmail();
});

//**************************************************
/**********************************************
 * #image-container {
  display: flex;
  justify-content: center;
  align-items: center;
  margin-top: 20px;
}

.image-display {
  max-width: 80%;
  height: auto;
  border: 2px solid #ccc;
  border-radius: 10px;
}
 * ****/
"use strict";

// Récupérer les éléments du DOM
const imagesList = document.getElementById("images-list");
const imageContainer = document.getElementById("image-container");

// Écouteur d'événement pour les clics sur les liens d'images
imagesList.addEventListener("click", (event) => {
  // Empêcher le comportement par défaut des liens
  event.preventDefault();

  // Vérifier si l'élément cliqué est un lien
  if (event.target.tagName === "A") {
    const imageUrl = event.target.href;

    // Créer un élément image
    const imgElement = document.createElement("img");
    imgElement.src = imageUrl;
    imgElement.classList.add("image-display");

    // Vider le conteneur et ajouter la nouvelle image
    imageContainer.innerHTML = "";
    imageContainer.appendChild(imgElement);
  }
});