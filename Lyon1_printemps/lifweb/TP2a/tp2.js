"use strict";
console.info("app.js loading...");

console.info("...app.js loaded");

let count = 0; 

const decrementBtn = document.querySelector("#decrementBtn");
const counter = document.querySelector("#counter");
const incrementBtn = document.querySelector("#incrementBtn");

function updateCounter(count) {
  counter.textContent = count;
}


decrementBtn.addEventListener("click", () => {
count = counter.textContent;
  updateCounter(count - 1);

});

incrementBtn.addEventListener("click", () => {
count = counter.textContent;
updateCounter(parseInt(count) + 1);
});

const resetBtn = document.createElement("button");
resetBtn.textContent = "Reset";

incrementBtn.after(resetBtn);

resetBtn.addEventListener("click", () => {
  count = counter.textContent;
  updateCounter(0)
});

//*********************************** */
//************Exercice 2 **********/

const Input_email = document.querySelector("#emailInput");
const btn_validation = document.querySelector("#validate-btn");
const message_erreur = document.querySelector("#errorMessage");

btn_validation.addEventListener("click", (event) => {
    console.log(Input_email.value)
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
        Input_email.style.backgroundColor = "lightgreen"
        errorMessage.textContent = "votre mail est valide ";

    }else{
        Input_email.style.backgroundColor = "lightcoral";
        errorMessage.textContent = "L'email n'est pas valide.";
    }   
}
