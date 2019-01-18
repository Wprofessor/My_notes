package com.company.FileTest;

import java.io.File;
import java.sql.SQLOutput;

public class FileDemo {
    public static void main(String[] args) {
        File readFile = new File("C:\\Users\\王教授\\Documents\\My notes\\java培训\\NewIo.txt");
        System.out.println(readFile.getName());
    }
}
