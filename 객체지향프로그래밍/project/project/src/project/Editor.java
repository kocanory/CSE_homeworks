package project;

import java.io.*;
public class Editor{
	
	int[] num;
	String findWord, fileName, input = null, select, number;//String�� ����
	
	String strTemp = null; //String�� ����
	String temp = null;
	int compare = 0;		
	static BufferedWriter bufferedWriter;
	final String FILE_OUT_PATH = "d:\\output.txt";
	final String TEXT_PATH = "d:\\test.txt"; //�ҷ��� �ؽ�Ʈ ���� ����
	final int BUFFER_SIZE = 30000000; //���� ������ ����
	FileWriter writer, wt;
	FileInputStream in;//���� �Է� ����� ���� ��ü�� ���� �� �ʱ�ȭ, �ؽ�Ʈ ������ �ҷ���;
	byte[] readBuffer = new byte[BUFFER_SIZE];
	BufferedInputStream bufferedInputStream = new BufferedInputStream(in, BUFFER_SIZE); //���۸� �̿��� �Է� ��ü�� ���� �� �ʱ�ȭ

	public static boolean loadWritingFile(String path, boolean isAppend)
	{		
		File textFile = new File(path);
		try
		{
			FileWriter fileWriter = new FileWriter(textFile, isAppend);
			bufferedWriter = new BufferedWriter(fileWriter);
		}
		catch(IOException e) //���ܰ� �߻��� ��� printStackTrace ����
		{
			e.printStackTrace();
			return false;
		}
		
		return true;
	}
}
