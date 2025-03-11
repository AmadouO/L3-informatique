const prom = new Promise((resolve, reject) => {
    //setTimeout(() => { resolve("promesse ok ") }, 3000);
    reject("promesse kpo")
});

/*prom.then(res => {
    console.log(res)
}).catch( err => {
    console.log(err)
});*/
prom.then(
    resultat => console.log(resultat),
    erreur => console.log(erreur)
);

