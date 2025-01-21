const equalityTest1 = "" == false;
console.log(`equalityTest1: ${equalityTest1}`);

const equalityTest2 = "" === false;
console.log(`equalityTest2: ${equalityTest2}`);

const equalityTest3 = "" === false;
console.log(`equalityTest3: ${equalityTest3}`);

const equalityTest4 = "" == 0;
console.log(`equalityTest4: ${equalityTest4}`);

const equalityTest5 = true == "true";
console.log(`equalityTest5: ${equalityTest5}`);

const equalityTest6 = true == "1";
console.log(`equalityTest6: ${equalityTest6}`);

const equalityTest7 = "10" + 5 == 15;
console.log(`equalityTest7: ${equalityTest7}`);

const equalityTest8 = "10" + 5 == 105;
console.log(`equalityTest8: ${equalityTest8}`);

const equalityTest9 = "10" + 5 === 105;
console.log(`equalityTest9: ${equalityTest9}`);
