let n = 42;
let b = false;
let s = "test";
let o = { name: "Aurélien", age: 42 };
let a = [0, 1, 1, 2, 3, 5, 8];
let f = function () {
  return 42;
};

function test1(num, bool, str, obj, arr) {
  num++;
  bool = !bool;
  str += "foo";
  obj.name = "Olivier";
  arr.push(13, 14);

  console.log(num, bool, str, obj, arr);
}

test1(n, b, s, o, a);
console.log(n, b, s, o, a);

function test2(obj, arr, fun) {
  obj = { foo: "bar" };
  arr = [42];
  fun = function () {
    return 0;
  };

  console.log(obj, arr, fun);
}

test2(o, a, f);
console.log(o, a, f);


function test1(num, bool, str, obj, arr) {
  num++;
  bool = !bool;
  str += "foo";
  obj.name = "Olivier";
  arr.push(13);

  console.log(num, bool, str, obj, arr);
}

test1(n, b, s, o, a);
console.log(n, b, s, o, a);

function test2(obj, arr, fun) {
  obj = { foo: "bar" };
  arr = [42];
  fun = function () {
    return 0;
  };

  console.log(obj, arr, fun);
}

test2(o, a, f);
console.log(o, a, f);
