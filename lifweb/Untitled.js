let fred = (arr) => arr.reduce((acc,x) => acc || x, false);
console.log(fred([1,2,3,4,5])); // false
console.log(fred([0,1,2,3,4,5])); // true
console.log(fred([0,0,0,0,0,0])); // false
console.log(fred([1,1,1,1,1,1])); // true
console.log(fred([1,0,1,1,1,1])); // true
console.log(fred([1,0,0,0,0,0])); // true
console.log(fred([0,0,0,0,0,1])); // true