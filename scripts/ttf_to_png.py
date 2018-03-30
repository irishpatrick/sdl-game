#!/usr/bin/python3

from PIL import Image
import sys
import os
import subprocess

def main(argv):
    argc = len(argv)
    if argc == 4:
        font = argv[1]
        png_dir = argv[2]
        pointsize = argv[3]

    else:
        print("error: not enough args")
        sys.exit(0)

    chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"

    for c in chars:
        try:
            subprocess.call(["convert -background none -fill black -font " + font + " -pointsize " + pointsize + " label:\"" + c + "\" " + os.path.join(png_dir, c + ".png"])
        except OSError:
            print ("you might need to install imagemagik")
            sys.exit(1)

    try:
        tmp = Image.open(os.path.join(png_dir, "a.png"))
    except IOError:
        exit(1)

    out = Image.new("RGBA", (tmp.size[0] * len(chars), tmp.size[1]), "none")

    x = 0
    y = 0
    w = tmp.size[0]
    h = tmp.size[1]

    n = 0;
    for c in chars:
        img = Image.open(os.path.join(png_dir, c + ".png"))
        reigon = img.crop((0,0,w,h))
        out.paste(reigon, ((x,y,w,h)))
        x += w * n
        n += 1

    out.save(os.path.join(png_dir, "out.png"), "PNG")

if __name__ == "__main__":
    main(sys.argv)
