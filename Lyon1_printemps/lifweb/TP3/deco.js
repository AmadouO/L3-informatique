function m(f) { // decorateur permettant de memoriser les arguments des appels à une fonction
    function w(...a) {  // w est une fonction qui prend un nombre variable d'arguments
      w.x.push(a); // ajouter les arguments a dans le tableau w.x
      return f(...a); // appeler la fonction f avec les arguments a
    }
  
    w.x = []; // initialiser le tableau w.x
    return w; // retourner la fonction w qui memorise les arguments des appels à la fonction f qui prend un nombre variable d'arguments
  }
  
  const adder_decorated = m((a, b) => a + b); // adder_decorated est une fonction qui memorise les arguments des appels à la fonction (a, b) => a + b
  
  console.log(adder_decorated(2, 3)); // affiche 5
  console.log(adder_decorated(3, 4)); // affiche 7