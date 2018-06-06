"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const util_1 = require("./util");
util_1.Util.test();
let canvas = document.getElementById('canvas');
let ctx = canvas.getContext('2d');
let now, then, delta;
let mouse = { x: 0, y: 0 };
canvas.addEventListener('mousemove', (e) => {
    mouse.x = e.x;
    mouse.y = e.y;
    document.getElementById('mousepos').innerHTML = mouse.x + ',' + mouse.y;
});
canvas.addEventListener('mousedown', (e) => {
});
canvas.addEventListener('mouseup', (e) => {
});
function init() {
    then = Date.now();
}
function update() {
    now = Date.now();
    delta = (now - then) / 1000.0;
    then = now;
}
function draw() {
    requestAnimationFrame(draw);
    util_1.Util.clear(ctx);
    update();
}
init();
draw();
//# sourceMappingURL=index.js.map