class Asset {

    public x: number;
    public y: number;
    private image: any;
    private ready: boolean;

    public constructor() {
        this.x = 0;
        this.y = 0;
        this.ready = false;
        this.image = null;
    }

    private callback(): void {
        this.ready = true;
    }

    public loadImage(fn: string): void {
        this.image = new Image();
        this.image.onload = this.callback;
        this.image.src = fn;
    }

    public isReady(): boolean {
        return this.ready;
    }
}

export {Asset};