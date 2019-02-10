package edu.pitt.pmr25.pack;

import java.io.File;
import java.util.ArrayList;
import org.apache.commons.io.FilenameUtils;
import ar.com.hjg.pngj.PngWriter;
import ar.com.hjg.pngj.PngReader;

/**
 * Hello world!
 *
 */
public class App 
{
    private static void pack(ArrayList<File> inputs, File output)
    {
        PngReader current = null;
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
