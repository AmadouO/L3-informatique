function iterate_array_forof(arr) {
  console.log("for...of");
  for (const elem of arr ){
    console.log(elem);
  }
}

function iterate_array_forin(arr) {
  console.log("for...in");
  for (const elem in arr){
    console.log(`${elem}: ${arr[elem]}`) 
  }
}

function iterate_array_for(arr) {
  console.log("for");
  for (let el = 0; el < arr.length; el++) {
    const element = arr[el];
    console.log(element);
  }
}

function iterate_array_while(arr) {
  console.log("while");
  let i = 0;
  while(i < arr.length){
    console.log(i);
    i++;
  }
}

function iterate_array_foreach(arr) {
  console.log("forEach");
  arr.forEach((element) => console.log(element));
}

function test() {
  // remplacer iterate_array par la fonction que vous souhaitez tester
  iterate_array_foreach([1, 2, 3, 6, 5, 4]);
  iterate_array_foreach([
    { a: 0, b: 1 },
    { a: 1, b: 42 },
  ]);
}
test();
