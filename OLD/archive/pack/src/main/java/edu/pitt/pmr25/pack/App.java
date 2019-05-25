package edu.pitt.pmr25.pack;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import javax.imageio.ImageIO;
import org.apache.commons.io.FilenameUtils;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;

public class App 
{
    private static int compare(BufferedImage a, BufferedImage b)
    {
        int sa = a.getHeight();
        int sb = a.getHeight();

        return sa - sb;
    }

    private static int getSize(BufferedImage a)
    {
        return a.getHeight();
    }

    private static <T> void swap(T[] array, int a, int b)
    {
        T tmp = array[a];
        array[a] = array[b];
        array[b] = tmp;
    }

    private static void pack(ArrayList<File> inputs, File output)
    {
        BufferedImage current = null;
        BufferedImage out = new BufferedImage(8192, 8192, BufferedImage.TYPE_INT_ARGB);
        Graphics2D g = (Graphics2D) out.getGraphics();
        int tileSize = 64;
        int x = 0;
        int y = 0;
        int maxw = 1024;

        BufferedImage[] images = new BufferedImage[inputs.size()];

        int i = 0;
        for (File e : inputs)
        {
            try
            {
                images[i++] = ImageIO.read(e);
            }
            catch (IOException ex)
            {

            }
        }

        // sort images by size
        i = 1;
        int j;
        while (i < images.length)
        {
            j = i;
            while (j > 0 && compare(images[j-1], images[j]) > 0)
            {
                swap(images, j, j-1);
                j--;
            }
            i++;
        }

        for (i=0; i<images.length; i++)
        {
            System.out.println("size: " + getSize(images[i]));
        }

        // pack images
        int ny = 0;
        for (i=0; i<images.length; i++)
        {
            g.drawImage(images[i], x, y, null);
            x += images[i].getWidth();
            if (images[i].getHeight() > ny)
            {
                ny = images[i].getHeight();
            }
            if (x > maxw)
            {
                x = 0;
                y += ny;
                if (i+1 < images.length)
                {
                    ny = images[i+1].getHeight();
                }
                ny = 0;
            }
        }
        try
        {
            ImageIO.write(out, "png", output);
        }
        catch (IOException e)
        {
            
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
