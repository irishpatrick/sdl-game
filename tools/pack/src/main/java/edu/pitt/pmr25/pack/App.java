package edu.pitt.pmr25.pack;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import javax.imageio.ImageIO;
import org.apache.commons.io.FilenameUtils;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;

/**
 * Hello world!
 *
 */
public class App 
{
    private static void pack(ArrayList<File> inputs, File output)
    {
        BufferedImage current = null;
        BufferedImage out = new BufferedImage(8*64, 8*64, BufferedImage.TYPE_INT_ARGB);
        Graphics2D g = (Graphics2D) out.getGraphics();
        int tileSize = 64;
        int x = 0;
        int y = 0;

        for (File e : inputs)
        {
            try
            {
                current = ImageIO.read(e);
            }
            catch (IOException ex)
            {
                System.out.println("failed to open image");
                current = null;
                continue;
            }

            if (current == null)
            {
                System.out.println("current is null");
            }
            g.drawImage(current, x*tileSize, y*tileSize, null);
            x++;
            if (x == 8)
            {
                x = 0;
                y++;
            }
        }

        try
        {
            ImageIO.write(out, "png", output);
        }
        catch (IOException ex)
        {
            System.out.println("couldn't write output image");
        }
    }

    public static void main( String[] args )
    {
        System.out.println("Hello World!");
        if (args.length < 2)
        {
            System.out.println("usage: pack <directory> <output> [-flags]");
            return;
        }

        String dir = args[0];
        String output = args[1];

        File folder = new File(dir);
        if (!folder.isDirectory())
        {
            System.out.println("bad directory");
            return;
        }

        File[] all = folder.listFiles();
        ArrayList<File> imgList = new ArrayList<>();

        for (int i=0; i<all.length; i++)
        {
            File c = all[i];
            if (c.isFile())
            {
                if (FilenameUtils.getExtension(c.getName()).equals("png"))
                {
                    System.out.println("Adding file " + c.getName());
                    imgList.add(c);
                }
            }
        }

        if (imgList.size() <= 0)
        {
            System.out.println("no .png files in directory");
            return;
        }

        pack(imgList, new File(output));
    }
}
