let canvas = document.getElementById('canvas');
let parent = canvas.parentNode;
let ctx = canvas.getContext("2d");
let clearColor = [0,0,0];

canvas.width = parent.style.width;
canvas.height = window.innerHeight;

function clear() {
    ctx.fillStyle = 'rgb(0,0,0)';
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    console.log('cleared');
}

function draw() {
    clear();

    requestAnimationFrame(draw);
}

draw();