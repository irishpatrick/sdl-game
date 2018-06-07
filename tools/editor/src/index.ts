import {Util} from "./util";
import {Viewport} from "./viewport";

let viewport: Viewport = new Viewport();
let canvas: any = document.getElementById('canvas');
let ctx = canvas.getContext('2d');
let now: number, then: number, delta: number;
let mouse: any = {x: 0, y: 0};

canvas.addEventListener('mousemove', (e: any) => {
    mouse.x = e.x;
    mouse.y = e.y;
    document.getElementById('mousepos').innerHTML = mouse.x + ',' + mouse.y;
});

canvas.addEventListener('mousedown', (e: any) => {

});

canvas.addEventListener('mouseup', (e: any) => {

});

function init() {
    Util.setClearColor(100,100,100);

    then = Date.now();
}

function update() {
    now = Date.now();
    delta = (now - then) / 1000.0;
    then = now;


}

function draw() {
    requestAnimationFrame(draw);

    Util.clear(ctx);
    update();
}

init();
draw();