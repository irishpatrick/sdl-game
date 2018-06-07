import {Viewport} from "./viewport";
import {Asset} from "./asset";

class Util {

    private static clearColor: number[] = [0, 0, 0];

    public static setClearColor(r: number, g: number, b: number): void {
        this.clearColor = [r, g, b];
    }

    public static clear(ctx: any): void {
        ctx.fillStyle = 'rgb(' + 
            this.clearColor[0] + ',' + 
            this.clearColor[1] + ',' + 
            this.clearColor[2] + ')';
        ctx.fillRect(0, 0, ctx.canvas.clientWidth, ctx.canvas.clientHeight);
    }

    public static draw(ctx: any, asset: Asset, view?: Viewport): void {
        let sx: number = 0;
        let sy: number = 0;
        if (view) {
            sx = (asset.x + view.x) * view.scale;
            sy = (asset.y + view.y) * view.scale;
        }

    }

    public static drawGrid(ctx: any, view: Viewport): void {
        let spacing: number = 32 * view.scale;
    }

}

export {Util};