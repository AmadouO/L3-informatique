"use strict";
console.info("app.js loading...");

console.info("...app.js loaded");

const count = 0; 
const operationPointer = 0;
let history = [0];  // Historique des valeurs du compteur




const decrementBtn = document.querySelector("#decrementBtn");
const counter = document.querySelector("#counter");
const incrementBtn = document.querySelector("#incrementBtn");

const btn_undo = document.querySelector("#btn_undo");
const btn_redo = document.querySelector("#btn_redo");
/*
// Mettre à jour le compteur et stocker l'opération dans l'historique
function updateCounter(newCount, saveHistory = true) {
  count = newCount;
  counter.textContent = count;

  if (saveHistory) {
    history = history.slice(0, operationPointer + 1);  // Supprime les valeurs "refaites"
    history.push(count);
    operationPointer++;
  }

  // Désactiver les boutons si nécessaire
  btn_undo.disabled = operationPointer === 0;
  btn_redo.disabled = operationPointer === history.length - 1;
}*/
function updateCounter(count) {
  counter.textContent = count;
}


decrementBtn.addEventListener("click", () => {
//count = counter.textContent;
  updateCounter(count - 1);

});

incrementBtn.addEventListener("click", () => {
  //count = counter.textContent;
  updateCounter(parseInt(count) + 1);
});

const resetBtn = document.createElement("button");
resetBtn.textContent = "Reset";

incrementBtn.after(resetBtn);

resetBtn.addEventListener("click", () => {
  //count = counter.textContent;
  updateCounter(0)
});

/*

// Undo / Redo
btn_undo.addEventListener("click", () => {
  if (operationPointer > 0) {
    operationPointer--;
    updateCounter(history[operationPointer], false);
  }
});

btn_redo.addEventListener("click", () => {
  if (operationPointer < history.length - 1) {
    operationPointer++;
    updateCounter(history[operationPointer], false);
  }
});

// Initialisation
updateCounter(0);*/

//*********************************** */
//************Exercice 2 **********/

const Input_email = document.querySelector("#emailInput");
const btn_validation = document.querySelector("#validate-btn");
const message_erreur = document.querySelector("#errorMessage");



btn_validation.addEventListener("click", (event) => {
    event.preventDefault(); 
    validationEmail();
   

  });
  
  
Input_email.addEventListener("input", () => {
    validationEmail();
  });

function validationEmail(){
    
  const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
  let emailCorrectementFormatte = emailRegex.test(Input_email.value);

    if(emailCorrectementFormatte){
       Input_email.style.backgroundColor = "lightgreen";
       errorMessage.textContent = "votre mail est valide ";

    }else{
        Input_email.style.backgroundColor = "lightcoral";
        errorMessage.textContent = "L'email n'est pas valide.";
    }   
}

/**###############################Exercice 3###################"""" */

const img_list = document.querySelector("#images-list");
const img_contaire = document.querySelector("#image-container");

img_list.addEventListener("click", (event) =>{
  event.preventDefault();

  if(event.target.tagName === "A"){
    const url_img = event.target.href; 
    const element_img = document.createElement("img");
    element_img.src = url_img;
    element_img.classList.add("affich_img");

    img_contaire.textContent = "";
    img_contaire.appendChild(element_img);
  }
})

//################################"Exercice 4#########################

const $grid = document.querySelector("#game-grid");

// Create 8x8 grid
for (let y = 0; y < 8; y++) {
  for (let x = 0; x < 8; x++) {
    const cell = document.createElement("div");
    cell.classList.add("grid-cell");
    cell.dataset.x = x;
    cell.dataset.y = y;
    $grid.appendChild(cell);
  }
}

let playerPosition = { x: 4, y: 4 };

function updatePlayerPosition() {
  // Remove previous player cell
  document.querySelector(".player")?.classList.remove("player");

  // Add player to new cell
  const cell = document.querySelector(
    `.grid-cell[data-x="${playerPosition.x}"][data-y="${playerPosition.y}"]`,
  );
  cell.classList.add("player");
}

updatePlayerPosition(); // Afficher le joueur au chargement


document.addEventListener("keydown", (event) => {
  switch (event.key) {
    case "ArrowUp":
      if (playerPosition.y > 0) playerPosition.y--;
      break;
    case "ArrowDown":
      if (playerPosition.y < 7) playerPosition.y++;
      break;
    case "ArrowLeft":
      if (playerPosition.x > 0) playerPosition.x--;
      break;
    case "ArrowRight":
      if (playerPosition.x < 7) playerPosition.x++;
      break;
  }
  
  updatePlayerPosition();
});

//############################## Exercice 5 ##############################

let tracking = false; // État du traqueur
let mousePos = { x: 0, y: 0 }; // Stocke la position de la souris
let trackerInterval = null; // Stocke l'intervalle// Undo / Redo
btn_undo.addEventListener("click", () => {
  if (operationPointer > 0) { //
    operationPointer--;
    updateCounter();
  }
});
btn_redo.addEventListener("click", () => {
  if (operationPointer < 0 ) {
    operationPointer++;
    updateCounter();
  }
});
let animationFrame = null; // Stocke l'ID de requestAnimationFrame

// Création du div .dot
const circle = document.createElement("div");
circle.classList.add("dot");
circle.style.display = "none"; // Caché par défaut
document.body.appendChild(circle);

// Met à jour la position de la souris
function followMouse() {
  document.addEventListener("mousemove", (event) => {
    mousePos.x = event.clientX; 
    mousePos.y = event.clientY;
  });

  function updatePosition() {
    circle.style.left = `${mousePos.x - 25}px`; // Centrer le point 
    circle.style.top = `${mousePos.y - 25}px`; 
    animationFrame = requestAnimationFrame(updatePosition); // Appel récursif pour suivre la souris en temps réel 
  }

  trackerInterval = setInterval(updatePosition, 50);  
}

// Gestion du bouton "Follow mouse"
const mouse_btn = document.querySelector("#mouse-btn");
mouse_btn.addEventListener("click", () => {
  if (!tracking) { 
    // Activer le traqueur
    circle.style.display = "block";
    followMouse();
  } else {
    // Désactiver le traqueur
    circle.style.display = "none";
    clearInterval(trackerInterval); 
    cancelAnimationFrame(animationFrame); 
    document.removeEventListener("mousemove", followMouse);
  }
  tracking = !tracking; // Inverser l'état
});

//############################## Exercice 6 ##############################

// Récupération du tableau et du thead
const table = document.querySelector("#the-table");
const thead = table.querySelector("thead");

// État des tris pour chaque colonne
let sortStates = {};

// Fonction pour trier les lignes du tableau
function sortTable(columnIndex, type, ascending) {
  const tbody = table.querySelector("tbody"); // Récupérer le tbody du tableau qui contient les lignes
  const rows = Array.from(tbody.querySelectorAll("tr")); 

  rows.sort((rowA, rowB) => {
    let cellA = rowA.cells[columnIndex].textContent.trim(); // Récupérer le contenu de la cellule 
    let cellB = rowB.cells[columnIndex].textContent.trim();

    // Conversion en fonction du type
    if (type === "number") {
      cellA = parseFloat(cellA) || 0;
      cellB = parseFloat(cellB) || 0;
    } else if (type === "date") {
      cellA = new Date(cellA);
      cellB = new Date(cellB);
    } else {
      cellA = cellA.toLowerCase();
      cellB = cellB.toLowerCase();
    }

    let comparison = 0;
    if (cellA < cellB) comparison = -1; //si cellule A est inférieur à cellule B on retourne -1 
    if (cellA > cellB) comparison = 1; //si cellule A est supérieur à cellule B on retourne 1
    
    return ascending ? comparison : -comparison; 
  });

  // Réinsérer les lignes triées dans le tableau
  tbody.append(...rows);
}

// Ajout de l'écouteur sur le thead pour la délégation d'événements
thead.addEventListener("click", (event) => {
  const th = event.target.closest("th");
  if (!th || !th.dataset.type) return; // Vérifie si l'élément cliqué est un <th> avec un data-type

  const columnIndex = th.cellIndex;
  const type = th.dataset.type;

  // Alterner entre croissant et décroissant
  sortStates[columnIndex] = !sortStates[columnIndex];

  sortTable(columnIndex, type, sortStates[columnIndex]);
});


//############################## Exercice 1 bis bonus ############################




