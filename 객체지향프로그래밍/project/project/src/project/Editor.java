package project;

import java.io.*;
public class Editor{
	
	int[] num;
	String findWord, fileName, input = null, select, number;//String을 선언
	
	String strTemp = null; //String을 선언
	String temp = null;
	int compare = 0;		
	static BufferedWriter bufferedWriter;
	final String FILE_OUT_PATH = "d:\\output.txt";
	final String TEXT_PATH = "d:\\test.txt"; //불러올 텍스트 파일 설정
	final int BUFFER_SIZE = 30000000; //버퍼 사이즈 설정
	FileWriter writer, wt;
	FileInputStream in;//파일 입력 기능을 위한 객체를 생성 및 초기화, 텍스트 파일을 불러옴;
	byte[] readBuffer = new byte[BUFFER_SIZE];
	BufferedInputStream bufferedInputStream = new BufferedInputStream(in, BUFFER_SIZE); //버퍼를 이용한 입력 객체를 생성 및 초기화

	public static boolean loadWritingFile(String path, boolean isAppend)
	{		
		File textFile = new File(path);
		try
		{
			FileWriter fileWriter = new FileWriter(textFile, isAppend);
			bufferedWriter = new BufferedWriter(fileWriter);
		}
		catch(IOException e) //예외가 발생할 경우 printStackTrace 실행
		{
			e.printStackTrace();
			return false;
		}
		
		return true;
	}
}
