const {app, BrowserWindow} = require('electron')
let win

function createWindow() {
    win = new BrowserWindow({width: 1024, height: 768})
    win.loadFile('dist/index.html')
    win.on('closed', () => {
        win = null;
    })
    win.openDevTools();
}

app.on('ready', createWindow)

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
        app.quit()
    }
})

app.on('activate', () => {
    if (win === null) {
        createWindow()
    }
})
